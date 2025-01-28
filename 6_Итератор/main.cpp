#include <iostream>
#include <vector>
#include <stack>

// Предварительное объявление шаблонного класса Iterator
template <typename T>
class Iterator;

// Базовый класс Glyph
class Glyph {
public:
    virtual ~Glyph() {}
    virtual void Draw() = 0;
    virtual Iterator<Glyph*>* CreateIterator() = 0;
};

// Базовый класс Iterator
template <typename T>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual T CurrentItem() const = 0;
    virtual ~Iterator() {}
};

// NullIterator для листовых глифов
template <typename T>
class NullIterator : public Iterator<T> {
public:
    void First() override {}
    void Next() override {}
    bool IsDone() const override { return true; }
    T CurrentItem() const override { return nullptr; }
};

// Итератор для списка
template <typename T>
class ListIterator : public Iterator<T> {
private:
    const std::vector<T>* items;
    size_t current;
public:
    ListIterator(const std::vector<T>& items) : items(&items), current(0) {}

    void First() override {
        current = 0;
    }

    void Next() override {
        current++;
    }

    bool IsDone() const override {
        return current >= items->size();
    }

    T CurrentItem() const override {
        return (*items)[current];
    }
};

// Конкретный глиф Row, который содержит потомков
class Row : public Glyph {
private:
    std::vector<Glyph*> children;
public:
    void Draw() override {
        std::cout << "Drawing Row" << std::endl;
        for (auto child : children) {
            child->Draw();
        }
    }

    void Add(Glyph* glyph) {
        children.push_back(glyph);
    }

    Iterator<Glyph*>* CreateIterator() override {
        return new ListIterator<Glyph*>(children);
    }

    ~Row() {
        for (auto child : children) {
            delete child;
        }
    }
};

// Итератор для обхода в прямом порядке
template <typename T>
class PreorderIterator : public Iterator<T> {
private:
    std::stack<Iterator<T>*> iterators;
    T root;
public:
    PreorderIterator(T root) : root(root) {}

    void First() override {
        while (!iterators.empty()) {
            delete iterators.top();
            iterators.pop();
        }
        Iterator<T>* i = root->CreateIterator();
        if (i) {
            i->First();
            iterators.push(i);
        }
    }

    void Next() override {
        if (iterators.empty()) return;

        Iterator<T>* topIterator = iterators.top();
        Glyph* currentGlyph = topIterator->CurrentItem();

        // Создаем итератор для текущего элемента, если он есть
        Iterator<T>* childIterator = currentGlyph->CreateIterator();
        if (childIterator) {
            childIterator->First();
            if (!childIterator->IsDone()) {
                iterators.push(childIterator);
                return;
            } else {
                delete childIterator;
            }
        }

        // Если текущий элемент не имеет потомков или они уже обработаны,
        // переходим к следующему элементу на текущем уровне
        topIterator->Next();
        while (!iterators.empty() && iterators.top()->IsDone()) {
            delete iterators.top();
            iterators.pop();
            if (!iterators.empty()) {
                iterators.top()->Next();
            }
        }
    }

    bool IsDone() const override {
        return iterators.empty();
    }

    T CurrentItem() const override {
        return iterators.empty() ? nullptr : iterators.top()->CurrentItem();
    }

    ~PreorderIterator() {
        while (!iterators.empty()) {
            delete iterators.top();
            iterators.pop();
        }
    }
};

// Конкретный глиф Character
class Character : public Glyph {
private:
    char ch;
public:
    Character(char ch) : ch(ch) {}

    void Draw() override {
        std::cout << "Drawing Character: " << ch << std::endl;
    }

    Iterator<Glyph*>* CreateIterator() override {
        return new NullIterator<Glyph*>();
    }
};

int main() {
    Row* row = new Row();
    Row* row2 = new Row();
    row2->Add(new Character('D'));
    row2->Add(new Character('E'));
    row->Add(row2);
    row->Add(new Character('B'));
    row->Add(new Character('C'));

    Iterator<Glyph*>* iterator = new PreorderIterator<Glyph*>(row);
    for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
        Glyph* current = iterator->CurrentItem();
        current->Draw();
    }

    delete iterator;
    delete row;

    return 0;
}