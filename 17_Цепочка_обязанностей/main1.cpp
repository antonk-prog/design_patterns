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

    virtual void handleRequest(const std::string& request) {
        if (nextHandler) {
            nextHandler->handleRequest(request);
        } else {
            std::cout << "Ни один обработчик не смог обработать запрос: " << request << std::endl;
        }
    }

    virtual ~Handler() = default;
};

// Конкретный обработчик для обработки запросов типа "A"
class ConcreteHandlerA : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "A") {
            std::cout << "ConcreteHandlerA обработал запрос: " << request << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

// Конкретный обработчик для обработки запросов типа "B"
class ConcreteHandlerB : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "B") {
            std::cout << "ConcreteHandlerB обработал запрос: " << request << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

// Конкретный обработчик для обработки запросов типа "C"
class ConcreteHandlerC : public Handler {
public:
    void handleRequest(const std::string& request) override {
        if (request == "C") {
            std::cout << "ConcreteHandlerC обработал запрос: " << request << std::endl;
        } else {
            Handler::handleRequest(request);
        }
    }
};

int main() {
    // Создаем цепочку обработчиков
    Handler* handlerA = new ConcreteHandlerA();
    Handler* handlerB = new ConcreteHandlerB();
    Handler* handlerC = new ConcreteHandlerC();

    // Настраиваем цепочку
    handlerA->setNextHandler(handlerB);
    handlerB->setNextHandler(handlerC);

    // Отправляем запросы
    handlerA->handleRequest("A");  // Обработает ConcreteHandlerA
    handlerA->handleRequest("B");  // Обработает ConcreteHandlerB
    handlerA->handleRequest("C");  // Обработает ConcreteHandlerC
    handlerA->handleRequest("D");  // Ни один обработчик не сможет обработать

    // Освобождаем память
    delete handlerA;
    delete handlerB;
    delete handlerC;

    return 0;
}