#include <iostream>
#include <memory>
#include <string>

// Предварительное объявление класса Document (необходимо для методов состояний)
class Document;

// Абстрактное состояние
class DocumentState {
public:
    virtual void publish(Document* document) = 0;
    virtual void edit(Document* document, const std::string& newContent) = 0;
    virtual ~DocumentState() = default;
};

// --- Определение конкретных состояний ---

class DraftState : public DocumentState {
public:
    void publish(Document* document) override;
    void edit(Document* document, const std::string& newContent) override;
};

class ModerationState : public DocumentState {
public:
    void publish(Document* document) override;
    void edit(Document* document, const std::string& newContent) override;
};

class PublishedState : public DocumentState {
public:
    void publish(Document* document) override;
    void edit(Document* document, const std::string& newContent) override;
};

// --- Определение класса Document ---
class Document {
private:
    std::shared_ptr<DocumentState> state; // Текущее состояние
    std::string content; // Содержимое документа
public:
    Document(const std::string& content) : content(content) {
        // Начальное состояние — черновик.
        // Теперь DraftState является полным типом, и вызов make_shared корректен.
        setState(std::make_shared<DraftState>());
    }

    void setState(std::shared_ptr<DocumentState> newState) {
        state = newState;
    }

    void publish() {
        state->publish(this);
    }

    void edit(const std::string& newContent) {
        state->edit(this, newContent);
    }

    std::string getContent() const {
        return content;
    }

    void setContent(const std::string& newContent) {
        content = newContent;
    }
};

// --- Определение методов конкретных состояний ---

void DraftState::publish(Document* document) {
    std::cout << "Document is now under moderation." << std::endl;
    // Переход в состояние "На модерации"
    document->setState(std::make_shared<ModerationState>());
}

void DraftState::edit(Document* document, const std::string& newContent) {
    std::cout << "Editing draft. New content: " << newContent << std::endl;
    document->setContent(newContent);
}

void ModerationState::publish(Document* document) {
    std::cout << "Document is now published." << std::endl;
    // Переход в состояние "Опубликован"
    document->setState(std::make_shared<PublishedState>());
}

void ModerationState::edit(Document* document, const std::string& newContent) {
    std::cout << "Cannot edit document while it is under moderation." << std::endl;
}

void PublishedState::publish(Document* document) {
    std::cout << "Document is already published." << std::endl;
}

void PublishedState::edit(Document* document, const std::string& newContent) {
    std::cout << "Cannot edit document after it has been published." << std::endl;
}

int main() {
    Document document("Initial content");

    // Работа с документом
    document.edit("Updated content");  // Редактируем черновик
    document.publish();                // Переход в состояние "На модерации"
    document.publish();                // Переход в состояние "Опубликован"
    document.edit("Final content");    // Пытаемся редактировать опубликованный документ

    return 0;
}
