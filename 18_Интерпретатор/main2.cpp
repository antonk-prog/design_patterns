#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

// Контекст: таблица данных
struct Table {
    std::vector<std::unordered_map<std::string, std::string>> rows;
};

// Абстрактное выражение
class Expression {
public:
    virtual bool interpret(const std::unordered_map<std::string, std::string>& row) = 0;
    virtual ~Expression() = default;
};

// Терминальное выражение для сравнения
class CompareExpression : public Expression {
private:
    std::string key;
    std::string value;
    std::string op;
public:
    CompareExpression(const std::string& key, const std::string& value, const std::string& op)
        : key(key), value(value), op(op) {}

    bool interpret(const std::unordered_map<std::string, std::string>& row) override {
        if (op == "=") {
            return row.at(key) == value;
        } else if (op == ">") {
            return std::stoi(row.at(key)) > std::stoi(value);
        }
        return false;
    }
};

// Нетерминальное выражение для AND
class AndExpression : public Expression {
private:
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    AndExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    bool interpret(const std::unordered_map<std::string, std::string>& row) override {
        return left->interpret(row) && right->interpret(row);
    }
};

// Клиент: выполняет запрос
class Query {
private:
    std::shared_ptr<Expression> expression;
public:
    Query(std::shared_ptr<Expression> expression) : expression(expression) {}

    std::vector<std::unordered_map<std::string, std::string>> execute(const Table& table) {
        std::vector<std::unordered_map<std::string, std::string>> result;
        for (const auto& row : table.rows) {
            if (expression->interpret(row)) {
                result.push_back(row);
            }
        }
        return result;
    }
};

int main() {
    // Создаем таблицу с данными
    Table table;
    table.rows = {
        {{"name", "John"}, {"age", "30"}},
        {{"name", "Alice"}, {"age", "25"}},
        {{"name", "Bob"}, {"age", "40"}}
    };

    // Создаем выражения для запроса: age > 25 AND name = "John"
    auto ageExpr = std::make_shared<CompareExpression>("age", "25", ">");
    auto nameExpr = std::make_shared<CompareExpression>("name", "John", "=");
    auto queryExpr = std::make_shared<AndExpression>(ageExpr, nameExpr);

    // Выполняем запрос
    Query query(queryExpr);
    auto result = query.execute(table);

    // Выводим результат
    for (const auto& row : result) {
        std::cout << "Name: " << row.at("name") << ", Age: " << row.at("age") << std::endl;
    }

    return 0;
}