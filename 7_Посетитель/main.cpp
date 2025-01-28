#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Предварительное объявление классов
class Character;
class Row;
class Image;

// Базовый класс Visitor
class Visitor {
public:
    virtual void visitCharacter(Character* character) = 0;
    virtual void visitRow(Row* row) = 0;
    virtual void visitImage(Image* image) = 0;
};

// Базовый класс Glyph
class Glyph {
public:
    virtual void accept(Visitor& visitor) = 0;
};

// Класс Character
class Character : public Glyph {
public:
    Character(char ch) : character(ch) {}

    void accept(Visitor& visitor) override {
        visitor.visitCharacter(this);
    }

    char getCharCode() const {
        return character;
    }

private:
    char character;
};

// Класс Row
class Row : public Glyph {
public:
    void accept(Visitor& visitor) override {
        visitor.visitRow(this);
    }

    void addGlyph(Glyph* glyph) {
        glyphs.push_back(glyph);
    }

    const std::vector<Glyph*>& getGlyphs() const {
        return glyphs;
    }

private:
    std::vector<Glyph*> glyphs;
};

// Класс Image
class Image : public Glyph {
public:
    void accept(Visitor& visitor) override {
        visitor.visitImage(this);
    }
};

// Конкретный Visitor для проверки правописания
class SpellingChecker : public Visitor {
public:
    void visitCharacter(Character* character) override {
        char ch = character->getCharCode();
        if (isalpha(ch)) {
            currentWord += ch;
        } else {
            if (!currentWord.empty()) {
                if (isMisspelled(currentWord)) {
                    misspellings.push_back(currentWord);
                }
                currentWord.clear();
            }
        }
    }

    void visitRow(Row* row) override {
        for (Glyph* glyph : row->getGlyphs()) {
            glyph->accept(*this);
        }
    }

    void visitImage(Image* image) override {
        // Изображения не проверяем
    }

    const std::vector<std::string>& getMisspellings() const {
        return misspellings;
    }

private:
    std::string currentWord;
    std::vector<std::string> misspellings;

    bool isMisspelled(const std::string& word) {
        // Простая проверка на наличие слова в словаре
        // В реальной реализации здесь будет более сложная логика
        std::vector<std::string> dictionary = {"the", "quick", "brown", "fox"};
        return std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end();
    }
};

// Конкретный Visitor для расстановки переносов
class HyphenationVisitor : public Visitor {
public:
    void visitCharacter(Character* character) override {
        char ch = character->getCharCode();
        if (isalpha(ch)) {
            currentWord += ch;
        } else {
            if (!currentWord.empty()) {
                hyphenate(currentWord);
                currentWord.clear();
            }
        }
    }

    void visitRow(Row* row) override {
        for (Glyph* glyph : row->getGlyphs()) {
            glyph->accept(*this);
        }
    }

    void visitImage(Image* image) override {
        // Изображения не обрабатываем
    }

private:
    std::string currentWord;

    void hyphenate(const std::string& word) {
        // Простая логика расстановки переносов
        // В реальной реализации здесь будет более сложный алгоритм
        std::cout << "Hyphenating word: " << word << std::endl;
    }
};

int main() {
    // Создаем структуру документа
    Row* row = new Row();
    row->addGlyph(new Character('T'));
    row->addGlyph(new Character('e'));
    row->addGlyph(new Character('h'));
    row->addGlyph(new Character(' '));
    row->addGlyph(new Character('q'));
    row->addGlyph(new Character('u'));
    row->addGlyph(new Character('i'));
    row->addGlyph(new Character('c'));
    row->addGlyph(new Character('k'));
    row->addGlyph(new Character(' '));
    row->addGlyph(new Character('b'));
    row->addGlyph(new Character('r'));
    row->addGlyph(new Character('o'));
    row->addGlyph(new Character('w'));
    row->addGlyph(new Character('n'));
    row->addGlyph(new Character(' '));
    row->addGlyph(new Character('f'));
    row->addGlyph(new Character('o'));
    row->addGlyph(new Character('x'));
    row->addGlyph(new Character('.'));

    // Проверка правописания
    SpellingChecker spellingChecker;
    row->accept(spellingChecker);

    std::cout << "Misspelled words:" << std::endl;
    for (const std::string& word : spellingChecker.getMisspellings()) {
        std::cout << word << std::endl;
    }

    // Расстановка переносов
    HyphenationVisitor hyphenationVisitor;
    row->accept(hyphenationVisitor);

    // Очистка памяти
    delete row;

    return 0;
}