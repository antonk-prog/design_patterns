#include <iostream>
#include <string>
#include <memory>

// Базовый класс Enemy
class Enemy {
public:
    virtual ~Enemy() = default;
    virtual std::unique_ptr<Enemy> clone() const = 0;
    virtual void attack() const = 0;
    virtual void setHealth(int health) = 0;
    virtual void setDamage(int damage) = 0;
    virtual void printStats() const = 0;
};

// Класс Goblin
class Goblin : public Enemy {
public:
    Goblin(int health, int damage, const std::string& texture)
        : health(health), damage(damage), texture(texture) {}

    std::unique_ptr<Enemy> clone() const override {
        return std::make_unique<Goblin>(*this); // Клонирование через конструктор копирования
    }

    void attack() const override {
        std::cout << "Goblin attacks with " << damage << " damage!" << std::endl;
    }

    void setHealth(int health) override {
        this->health = health;
    }

    void setDamage(int damage) override {
        this->damage = damage;
    }

    void printStats() const override {
        std::cout << "Goblin stats: Health = " << health
                  << ", Damage = " << damage
                  << ", Texture = " << texture << std::endl;
    }

private:
    int health;
    int damage;
    std::string texture;
};

// Класс Dragon
class Dragon : public Enemy {
public:
    Dragon(int health, int damage, const std::string& texture)
        : health(health), damage(damage), texture(texture) {}

    std::unique_ptr<Enemy> clone() const override {
        return std::make_unique<Dragon>(*this); // Клонирование через конструктор копирования
    }

    void attack() const override {
        std::cout << "Dragon breathes fire with " << damage << " damage!" << std::endl;
    }

    void setHealth(int health) override {
        this->health = health;
    }

    void setDamage(int damage) override {
        this->damage = damage;
    }

    void printStats() const override {
        std::cout << "Dragon stats: Health = " << health
                  << ", Damage = " << damage
                  << ", Texture = " << texture << std::endl;
    }

private:
    int health;
    int damage;
    std::string texture;
};

int main() {
    // Создаем прототипы врагов
    std::unique_ptr<Enemy> goblinPrototype = std::make_unique<Goblin>(100, 10, "goblin_texture.png");
    std::unique_ptr<Enemy> dragonPrototype = std::make_unique<Dragon>(500, 50, "dragon_texture.png");

    // Клонируем прототипы для создания новых врагов
    std::unique_ptr<Enemy> goblin1 = goblinPrototype->clone();
    std::unique_ptr<Enemy> goblin2 = goblinPrototype->clone();
    std::unique_ptr<Enemy> dragon1 = dragonPrototype->clone();

    // Модифицируем клонированных врагов
    goblin1->setHealth(80);
    goblin2->setDamage(15);
    dragon1->setHealth(450);

    // Выводим информацию о врагах
    goblin1->printStats();
    goblin2->printStats();
    dragon1->printStats();

    // Атака врагов
    goblin1->attack();
    goblin2->attack();
    dragon1->attack();

    return 0;
}