#include <iostream>
#include <string>

// Целевой интерфейс, который ожидает клиент
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getDescription() const = 0;
};

// Адаптируемый класс (несовместимый интерфейс)
class LegacyTextView {
public:
    LegacyTextView(int x, int y, const std::string& text) 
        : x(x), y(y), text(text) {}

    void display() const {
        std::cout << "Legacy Text View at (" << x << ", " << y 
                  << "): " << text << std::endl;
    }

    int getX() const { return x; }
    int getY() const { return y; }
    std::string getContent() const { return text; }

private:
    int x, y;
    std::string text;
};

// Адаптер (преобразует LegacyTextView к интерфейсу Shape)
class TextShapeAdapter : public Shape {
public:
    TextShapeAdapter(const LegacyTextView& legacyView) 
        : legacyView(legacyView) {}

    void draw() const override {
        // Адаптация метода display() к draw()
        legacyView.display();
    }

    std::string getDescription() const override {
        // Адаптация данных LegacyTextView к строке
        return "Adapted Text: \"" + legacyView.getContent() 
               + "\" at (" + std::to_string(legacyView.getX()) 
               + ", " + std::to_string(legacyView.getY()) + ")";
    }

private:
    LegacyTextView legacyView;
};

// Клиентский код
int main() {
    // Создаем объект старого класса
    LegacyTextView legacyText(10, 20, "Hello Adapter Pattern!");

    // Обертываем его в адаптер
    Shape* adaptedText = new TextShapeAdapter(legacyText);

    // Работаем через целевой интерфейс
    adaptedText->draw();
    std::cout << adaptedText->getDescription() << std::endl;

    delete adaptedText;
    return 0;
}