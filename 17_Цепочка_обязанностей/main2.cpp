#include <iostream>
#include <string>

// Базовый класс обработчика
class Handler {
protected:
    Handler* nextHandler;

public:
    Handler() : nextHandler(nullptr) {}

    void setNextHandler(Handler* handler) {
        nextHandler = handler;
    }

    // Основной метод обработки запроса
    virtual void handleRequest(const std::string& user, const std::string& request) {
        if (nextHandler) {
            nextHandler->handleRequest(user, request);
        }
    }

    virtual ~Handler() = default;
};

// Обработчик для проверки аутентификации
class AuthenticationHandler : public Handler {
public:
    void handleRequest(const std::string& user, const std::string& request) override {
        if (user == "admin" || user == "user") {
            std::cout << "Аутентификация прошла успешно для пользователя: " << user << std::endl;
            Handler::handleRequest(user, request); // Передаем запрос дальше
        } else {
            std::cout << "Ошибка аутентификации: пользователь " << user << " не найден." << std::endl;
        }
    }
};

// Обработчик для проверки прав доступа
class AuthorizationHandler : public Handler {
public:
    void handleRequest(const std::string& user, const std::string& request) override {
        if (user == "admin") {
            std::cout << "Права доступа подтверждены для пользователя: " << user << std::endl;
            Handler::handleRequest(user, request); // Передаем запрос дальше
        } else {
            std::cout << "Ошибка доступа: пользователь " << user << " не имеет прав на выполнение действия." << std::endl;
        }
    }
};

// Обработчик для логирования запроса
class LoggingHandler : public Handler {
public:
    void handleRequest(const std::string& user, const std::string& request) override {
        std::cout << "Запрос пользователя " << user << " успешно обработан: " << request << std::endl;
        // Логирование завершено, цепочка завершается
    }
};

int main() {
    // Создаем цепочку обработчиков
    Handler* authHandler = new AuthenticationHandler();
    Handler* authzHandler = new AuthorizationHandler();
    Handler* loggingHandler = new LoggingHandler();

    // Настраиваем цепочку
    authHandler->setNextHandler(authzHandler);
    authzHandler->setNextHandler(loggingHandler);

    // Пример запросов
    std::cout << "--- Запрос от пользователя 'admin' ---" << std::endl;
    authHandler->handleRequest("admin", "удалить данные");

    std::cout << "\n--- Запрос от пользователя 'user' ---" << std::endl;
    authHandler->handleRequest("user", "изменить данные");

    std::cout << "\n--- Запрос от пользователя 'guest' ---" << std::endl;
    authHandler->handleRequest("guest", "просмотреть данные");

    // Освобождаем память
    delete authHandler;
    delete authzHandler;
    delete loggingHandler;

    return 0;
}