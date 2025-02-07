#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// Абстрактное выражение
class Expression {
public:
    virtual int interpret(std::unordered_map<std::string, int>& context) = 0;
    virtual ~Expression() = default;
};

// Терминальное выражение для переменной
class VariableExpression : public Expression {
private:
    std::string name;
public:
    VariableExpression(const std::string& name) : name(name) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return context[name];
    }
};

// Терминальное выражение для числа
class NumberExpression : public Expression {
private:
    int number;
public:
    NumberExpression(int number) : number(number) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return number;
    }
};

// Нетерминальное выражение для сложения
class AddExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return left->interpret(context) + right->interpret(context);
    }
};

// Нетерминальное выражение для вычитания
class SubtractExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    SubtractExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return left->interpret(context) - right->interpret(context);
    }
};

int main() {
    // Контекст с переменными
    std::unordered_map<std::string, int> context = {
        {"x", 10},
        {"y", 5}
    };

    // Создаем выражения: x + y - 2
    auto x = std::make_shared<VariableExpression>("x");
    auto y = std::make_shared<VariableExpression>("y");
    auto two = std::make_shared<NumberExpression>(2);

    auto add = std::make_shared<AddExpression>(x, y);
    auto expression = std::make_shared<SubtractExpression>(add, two);

    // Интерпретируем выражение
    int result = expression->interpret(context);
    std::cout << "Result: " << result << std::endl; // Output: Result: 13

    return 0;
}