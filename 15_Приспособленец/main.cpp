#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

// Внутреннее состояние: общие атрибуты символов
struct SharedState {
    std::string font;
    int size;
    std::string color;

    SharedState(const std::string& font, int size, const std::string& color)
        : font(font), size(size), color(color) {}

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss) {
        return os << "[Шрифт: " << ss.font << ", Размер: " << ss.size 
                  << ", Цвет: " << ss.color << "]";
    }
};

// Внешнее состояние: уникальные параметры символов
struct UniqueState {
    int x;
    int y;
    
    UniqueState(int x, int y) : x(x), y(y) {}
    
    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us) {
        return os << "(X: " << us.x << ", Y: " << us.y << ")";
    }
};

// Приспособленец: символ с внутренним состоянием
class Character {
public:
    explicit Character(char symbol, const SharedState& state) 
        : symbol_(symbol), shared_state_(state) {}

    void draw(const UniqueState& unique_state) const {
        std::cout << "Символ '" << symbol_ << "' "
                  << shared_state_ << " " << unique_state << std::endl;
    }

private:
    char symbol_;
    SharedState shared_state_;
};

// Фабрика приспособленцев
class GlyphFactory {
public:
    std::shared_ptr<Character> getCharacter(char symbol, const SharedState& state) {
        // Ключ: символ + хеш общего состояния
        size_t key = std::hash<std::string>{}(std::string(1, symbol) + state.font 
                       + std::to_string(state.size) + state.color);
        
        if (characters_.find(key) == characters_.end()) {
            characters_[key] = std::make_shared<Character>(symbol, state);
        }
        return characters_[key];
    }

private:
    std::unordered_map<size_t, std::shared_ptr<Character>> characters_;
};

// Клиентский код
int main() {
    GlyphFactory factory;

    // Общие атрибуты для группы символов
    SharedState arial_12_black("Arial", 12, "Black");
    SharedState times_14_red("Times New Roman", 14, "Red");

    // Создаем "документ" с символами
    std::vector<std::pair<std::shared_ptr<Character>, UniqueState>> document;

    // Добавляем символы (повторно используем общие состояния)
    document.emplace_back(factory.getCharacter('A', arial_12_black), UniqueState(10, 20));
    document.emplace_back(factory.getCharacter('B', times_14_red), UniqueState(30, 40));
    document.emplace_back(factory.getCharacter('A', arial_12_black), UniqueState(50, 60)); // Повторное использование 'A'

    // Отрисовка
    for (const auto& [character, position] : document) {
        character->draw(position);
    }
    std::cout << document.size() << std::endl;
    return 0;
}