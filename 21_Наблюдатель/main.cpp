#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
// Абстрактный наблюдатель
class Observer {
public:
    virtual void update(const std::string& message) = 0;
    virtual ~Observer() = default;
};

// Конкретный наблюдатель: Пользователь
class User : public Observer {
private:
    std::string name;
public:
    User(const std::string& name) : name(name) {}

    void update(const std::string& message) override {
        std::cout << name << " received message: " << message << std::endl;
    }
};

// Субъект: Система уведомлений
class NotificationSystem {
private:
    std::vector<std::shared_ptr<Observer>> observers; // Список наблюдателей
    std::string message; // Состояние субъекта
public:
    void addObserver(const std::shared_ptr<Observer>& observer) {
        observers.push_back(observer);
    }

    void removeObserver(const std::shared_ptr<Observer>& observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() {
        for (const auto& observer : observers) {
            observer->update(message);
        }
    }

    void setMessage(const std::string& newMessage) {
        message = newMessage;
        notifyObservers(); // Уведомляем всех наблюдателей
    }
};

int main() {
    // Создаем систему уведомлений
    NotificationSystem system;

    // Создаем пользователей (наблюдателей)
    auto alice = std::make_shared<User>("Alice");
    auto bob = std::make_shared<User>("Bob");

    // Подписываем пользователей на уведомления
    system.addObserver(alice);
    system.addObserver(bob);

    // Публикуем уведомление
    system.setMessage("New update available!");

    // Отписываем одного пользователя
    system.removeObserver(bob);

    // Публикуем еще одно уведомление
    system.setMessage("Maintenance scheduled for tomorrow.");

    return 0;
}