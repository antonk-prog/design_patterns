#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
// Базовый класс графического объекта
class Graphic {
public:
    virtual ~Graphic() = default;
    virtual void Draw() const = 0;
    
    // Методы для работы с детьми (реализованы только в композите)
    virtual void Add(std::shared_ptr<Graphic> g) {
        throw std::runtime_error("Невозможно добавить элемент к примитиву");
    }
    
    virtual void Remove(std::shared_ptr<Graphic> g) {
        throw std::runtime_error("Невозможно удалить элемент из примитива");
    }
    
    virtual std::shared_ptr<Graphic> GetChild(int index) {
        throw std::runtime_error("Примитив не содержит детей");
    }
};

// Листовые объекты
class Line : public Graphic {
public:
    void Draw() const override {
        std::cout << "Рисуем линию\n";
    }
};

class Rectangle : public Graphic {
public:
    void Draw() const override {
        std::cout << "Рисуем прямоугольник\n";
    }
};

class Text : public Graphic {
public:
    void Draw() const override {
        std::cout << "Выводим текст\n";
    }
};

class Picture : public Graphic {
public:
    void Draw() const override {
        std::cout << "Отображаем изображение\n";
    }
};

// Композитная группа
class GraphicsGroup : public Graphic {
    std::vector<std::shared_ptr<Graphic>> children;
    
public:
    void Draw() const override {
        std::cout << "=== Начало группы ===\n";
        for (const auto& child : children) {
            child->Draw();
        }
        std::cout << "=== Конец группы ===\n\n";
    }
    
    void Add(std::shared_ptr<Graphic> g) override {
        children.push_back(g);
    }
    
    void Remove(std::shared_ptr<Graphic> g) override {
        children.erase(
            std::remove(children.begin(), children.end(), g),
            children.end()
        );
    }
    
    std::shared_ptr<Graphic> GetChild(int index) override {
        if (index < 0 || index >= children.size()) {
            throw std::out_of_range("Неверный индекс");
        }
        return children[index];
    }
};

int main() {
    try {
        // Создаем листовые объекты
        auto line = std::make_shared<Line>();
        auto rect = std::make_shared<Rectangle>();
        auto text = std::make_shared<Text>();
        auto picture = std::make_shared<Picture>();

        // Создаем группы
        auto group1 = std::make_shared<GraphicsGroup>();
        group1->Add(line);
        group1->Add(rect);
        
        auto group2 = std::make_shared<GraphicsGroup>();
        group2->Add(text);
        group2->Add(picture);

        // Создаем корневую группу с вложенными группами
        auto root = std::make_shared<GraphicsGroup>();
        root->Add(group1);
        root->Add(group2);
        root->Add(std::make_shared<Line>());  // Добавляем отдельный элемент

        // Демонстрация работы
        std::cout << "Рисуем корневую группу:\n";
        root->Draw();

        // Тестирование методов
        std::cout << "Первый элемент корневой группы:\n";
        root->GetChild(0)->Draw();

        // Попытка добавить элемент к примитиву
        line->Add(rect);  // Выбросит исключение
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}