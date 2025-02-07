#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Memento: Хранитель состояния
class TextMemento {
private:
    std::string text; // Состояние текста
    friend class TextEditor; // Разрешаем TextEditor доступ к приватным полям

    TextMemento(const std::string& text) : text(text) {}

    std::string getText() const {
        return text;
    }
};

// Originator: Текстовый редактор
class TextEditor {
private:
    std::string text; // Текущий текст
public:
    void setText(const std::string& newText) {
        text = newText;
    }

    std::string getText() const {
        return text;
    }

    // Создает Memento с текущим состоянием
    std::unique_ptr<TextMemento> save() const {
        return std::unique_ptr<TextMemento>(new TextMemento(text)); // Создаем Memento напрямую
    }

    // Восстанавливает состояние из Memento
    void restore(const std::unique_ptr<TextMemento>& memento) {
        if (memento) {
            text = memento->getText();
        }
    }
};

// Caretaker: Управляет Memento
class History {
private:
    std::vector<std::unique_ptr<TextMemento>> mementos; // Список состояний
    TextEditor* editor; // Ссылка на текстовый редактор
public:
    History(TextEditor* editor) : editor(editor) {}

    // Сохраняет текущее состояние редактора
    void backup() {
        mementos.push_back(editor->save());
    }

    // Отменяет последнее изменение
    void undo() {
        if (!mementos.empty()) {
            editor->restore(std::move(mementos.back()));
            mementos.pop_back();
        } else {
            std::cout << "Nothing to undo." << std::endl;
        }
    }
};

int main() {
    // Создаем текстовый редактор и историю изменений
    TextEditor editor;
    History history(&editor);

    // Редактируем текст и сохраняем состояния
    editor.setText("Hello, World!");
    history.backup(); // Сохраняем состояние

    editor.setText("This is a new text.");
    history.backup(); // Сохраняем состояние

    editor.setText("Another change.");
    std::cout << "Current text: " << editor.getText() << std::endl;

    // Отменяем изменения
    history.undo();
    std::cout << "After undo: " << editor.getText() << std::endl;

    history.undo();
    std::cout << "After second undo: " << editor.getText() << std::endl;

    history.undo(); // Попытка отменить, когда больше нет состояний
    return 0;
}