#include <iostream>
#include <string>

// Абстрактный класс с шаблонным методом
class DocumentProcessor {
public:
    // Шаблонный метод
    void ProcessDocument(const std::string& filePath) {
        OpenDocument(filePath);
        ReadDocument();
        CloseDocument();
    }

    virtual ~DocumentProcessor() = default;

protected:
    // Примитивные операции, которые должны быть переопределены подклассами
    virtual void OpenDocument(const std::string& filePath) = 0;
    virtual void ReadDocument() = 0;
    virtual void CloseDocument() = 0;

    // Операция-зацепка (по умолчанию ничего не делает)
    virtual void OnDocumentProcessed() {
        std::cout << "Document processing completed." << std::endl;
    }
};

// Конкретный класс для обработки текстовых документов
class TextDocumentProcessor : public DocumentProcessor {
protected:
    void OpenDocument(const std::string& filePath) override {
        std::cout << "Opening text document: " << filePath << std::endl;
    }

    void ReadDocument() override {
        std::cout << "Reading text document..." << std::endl;
    }

    void CloseDocument() override {
        std::cout << "Closing text document." << std::endl;
    }

    void OnDocumentProcessed() override {
        std::cout << "Text document processing completed." << std::endl;
    }
};

// Конкретный класс для обработки PDF-документов
class PdfDocumentProcessor : public DocumentProcessor {
protected:
    void OpenDocument(const std::string& filePath) override {
        std::cout << "Opening PDF document: " << filePath << std::endl;
    }

    void ReadDocument() override {
        std::cout << "Reading PDF document..." << std::endl;
    }

    void CloseDocument() override {
        std::cout << "Closing PDF document." << std::endl;
    }
};

int main() {
    // Обработка текстового документа
    TextDocumentProcessor textProcessor;
    textProcessor.ProcessDocument("example.txt");

    // Обработка PDF-документа
    PdfDocumentProcessor pdfProcessor;
    pdfProcessor.ProcessDocument("example.pdf");

    return 0;
}