#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Предварительное объявление класса User
class User;

// Абстрактный посредник
class ChatMediator {
public:
    virtual void sendMessage(const std::string& message, User* user) = 0;
    virtual void addUser(User* user) = 0;
    virtual ~ChatMediator() = default;
};

// Конкретный посредник: Чат-комната
class ChatRoom : public ChatMediator {
private:
    std::vector<User*> users; // Список пользователей в чате
public:
    void addUser(User* user) override {
        users.push_back(user);
    }

    void sendMessage(const std::string& message, User* sender) override {
        for (auto user : users) {
            if (user != sender) { // Не отправляем сообщение отправителю
                user->receive(message);
            }
        }
    }
};

// Абстрактный класс пользователя
class User {
protected:
    std::string name;
    ChatMediator* mediator;
public:
    User(const std::string& name, ChatMediator* mediator)
        : name(name), mediator(mediator) {
        mediator->addUser(this);
    }

    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
    virtual ~User() = default;
};

// Конкретный пользователь
class ChatUser : public User {
public:
    ChatUser(const std::string& name, ChatMediator* mediator)
        : User(name, mediator) {}

    void send(const std::string& message) override {
        std::cout << name << " sends: " << message << std::endl;
        mediator->sendMessage(message, this);
    }

    void receive(const std::string& message) override {
        std::cout << name << " receives: " << message << std::endl;
    }
};

int main() {
    // Создаем посредника (чат-комнату)
    auto chatRoom = std::make_unique<ChatRoom>();

    // Создаем пользователей
    auto alice = std::make_unique<ChatUser>("Alice", chatRoom.get());
    auto bob = std::make_unique<ChatUser>("Bob", chatRoom.get());
    auto charlie = std::make_unique<ChatUser>("Charlie", chatRoom.get());

    // Пользователи отправляют сообщения
    alice->send("Hi everyone!");
    bob->send("Hello Alice!");
    charlie->send("Hey Bob, how are you?");

    return 0;
}