#include <iostream>
#include <vector>
#include <memory>

// Продукт - Лабиринт
class Maze {
public:
    void AddRoom(int room) {
        std::cout << "Добавлена комната №" << room << std::endl;
        rooms.push_back(room);
    }

    void AddDoor(int from, int to) {
        std::cout << "Добавлена дверь между комнатами №" << from << " и №" << to << std::endl;
        doors.emplace_back(from, to);
    }

    void Show() const {
        std::cout << "Лабиринт содержит " << rooms.size() << " комнат и " << doors.size() << " дверей:" << std::endl;
        for (int room : rooms) {
            std::cout << "Комната №" << room << std::endl;
        }
        for (const auto& door : doors) {
            std::cout << "Дверь между комнатами №" << door.first << " и №" << door.second << std::endl;
        }
    }

private:
    std::vector<int> rooms;
    std::vector<std::pair<int, int>> doors;
};

// Строитель
class MazeBuilder {
public:
    virtual ~MazeBuilder() = default;
    virtual void BuildMaze() = 0;
    virtual void BuildRoom(int room) = 0;
    virtual void BuildDoor(int from, int to) = 0;
    virtual std::unique_ptr<Maze> GetMaze() = 0;
};

// Конкретный строитель для стандартного лабиринта
class StandardMazeBuilder : public MazeBuilder {
private:
    std::unique_ptr<Maze> _currentMaze;
public:
    StandardMazeBuilder() : _currentMaze(nullptr) {}

    void BuildMaze() override {
        _currentMaze = std::make_unique<Maze>();
    }

    void BuildRoom(int room) override {
        if (_currentMaze) {
            _currentMaze->AddRoom(room);
        }
    }

    void BuildDoor(int from, int to) override {
        if (_currentMaze) {
            _currentMaze->AddDoor(from, to);
        }
    }

    std::unique_ptr<Maze> GetMaze() override {
        return std::move(_currentMaze);
    }
};

// Конкретный строитель для сложного лабиринта
class ComplexMazeBuilder : public MazeBuilder {
private:
    std::unique_ptr<Maze> _currentMaze;
public:
    ComplexMazeBuilder() : _currentMaze(nullptr) {}

    void BuildMaze() override {
        _currentMaze = std::make_unique<Maze>();
    }

    void BuildRoom(int room) override {
        if (_currentMaze) {
            _currentMaze->AddRoom(room);
            // Добавляем дополнительные комнаты вокруг основной
            _currentMaze->AddRoom(room * 10 + 1);
            _currentMaze->AddRoom(room * 10 + 2);
        }
    }

    void BuildDoor(int from, int to) override {
        if (_currentMaze) {
            _currentMaze->AddDoor(from, to);
            // Добавляем дополнительные двери
            _currentMaze->AddDoor(from * 10 + 1, to * 10 + 1);
            _currentMaze->AddDoor(from * 10 + 2, to * 10 + 2);
        }
    }

    std::unique_ptr<Maze> GetMaze() override {
        return std::move(_currentMaze);
    }
};

// Распорядитель
class MazeGame {
public:
    std::unique_ptr<Maze> CreateMaze(MazeBuilder& builder) {
        builder.BuildMaze();
        builder.BuildRoom(1);
        builder.BuildRoom(2);
        builder.BuildDoor(1, 2);
        return builder.GetMaze();
    }

    std::unique_ptr<Maze> CreateComplexMaze(MazeBuilder& builder) {
        builder.BuildMaze();
        builder.BuildRoom(1);
        builder.BuildRoom(2);
        builder.BuildRoom(3);
        builder.BuildDoor(1, 2);
        builder.BuildDoor(2, 3);
        builder.BuildDoor(3, 1);
        return builder.GetMaze();
    }
};

// Новый тип строителя - Лабиринт с секретными комнатами
class SecretMazeBuilder : public MazeBuilder {
private:
    std::unique_ptr<Maze> _currentMaze;
public:
    SecretMazeBuilder() : _currentMaze(nullptr) {}

    void BuildMaze() override {
        _currentMaze = std::make_unique<Maze>();
    }

    void BuildRoom(int room) override {
        if (_currentMaze) {
            _currentMaze->AddRoom(room);
            // Добавляем секретную комнату
            _currentMaze->AddRoom(room * 100);
        }
    }

    void BuildDoor(int from, int to) override {
        if (_currentMaze) {
            _currentMaze->AddDoor(from, to);
            // Добавляем секретную дверь
            _currentMaze->AddDoor(from * 100, to * 100);
        }
    }

    std::unique_ptr<Maze> GetMaze() override {
        return std::move(_currentMaze);
    }
};

int main() {
    MazeGame game;

    // Создание стандартного лабиринта
    StandardMazeBuilder standardBuilder;
    auto standardMaze = game.CreateMaze(standardBuilder);
    standardMaze->Show();

    // Создание сложного лабиринта
    ComplexMazeBuilder complexBuilder;
    auto complexMaze = game.CreateComplexMaze(complexBuilder);
    complexMaze->Show();

    // Создание лабиринта с секретными комнатами
    SecretMazeBuilder secretBuilder;
    auto secretMaze = game.CreateMaze(secretBuilder);
    secretMaze->Show();

    return 0;
}