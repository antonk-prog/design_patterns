#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Абстрактный продукт - экспортер данных
class DataExporter {
public:
    virtual void exportData(const std::vector<std::string>& data) const = 0;
    virtual ~DataExporter() = default;
};

// Конкретные продукты
class JsonExporter : public DataExporter {
public:
    void exportData(const std::vector<std::string>& data) const override {
        std::cout << "Экспорт данных в JSON:\n";
        std::cout << "{\n";
        for(size_t i = 0; i < data.size(); ++i) {
            std::cout << "  \"item" << i << "\": \"" << data[i] << "\""
                      << (i < data.size()-1 ? "," : "") << "\n";
        }
        std::cout << "}\n";
    }
};

class CsvExporter : public DataExporter {
public:
    void exportData(const std::vector<std::string>& data) const override {
        std::cout << "Экспорт данных в CSV:\n";
        for(const auto& item : data) {
            std::cout << "\"" << item << "\",";
        }
        std::cout << "\n";
    }
};

// Абстрактный создатель
class ExportHandler {
public:
    virtual ~ExportHandler() = default;
    
    // Фабричный метод
    virtual std::unique_ptr<DataExporter> createExporter() const = 0;
    
    // Общая логика обработки
    void processAndExport(const std::vector<std::string>& rawData) const {
        // Предварительная обработка данных
        auto processedData = preprocessData(rawData);
        
        // Создание экспортера через фабричный метод ИМЕННО ЗДЕСЬ ВСЯ СУТЬ ФАБР МЕТОДА
        auto exporter = createExporter();
        
        // Экспорт данных
        exporter->exportData(processedData);
    }

protected:
    virtual std::vector<std::string> preprocessData(
        const std::vector<std::string>& data) const 
    {
        // Базовая предобработка данных
        std::vector<std::string> processed;
        for(const auto& item : data) {
            processed.push_back(item.substr(0, 50)); // Обрезаем длинные строки
        }
        return processed;
    }
};

// Конкретные создатели
class JsonExportHandler : public ExportHandler {
public:
    std::unique_ptr<DataExporter> createExporter() const override {
        return std::make_unique<JsonExporter>();
    }
};

class CsvExportHandler : public ExportHandler {
public:
    std::unique_ptr<DataExporter> createExporter() const override {
        return std::make_unique<CsvExporter>();
    }

protected:
    std::vector<std::string> preprocessData(
        const std::vector<std::string>& data) const override 
    {
        // Специфичная для CSV предобработка
        std::vector<std::string> processed;
        for(const auto& item : data) {
            std::string cleaned;
            for(char c : item) {
                if(c != ',') cleaned += c; // Удаляем запятые
            }
            processed.push_back(cleaned.substr(0, 30));
        }
        return processed;
    }
};

int main() {
    std::vector<std::string> rawData = {
        "Product 1, Price: $19.99",
        "Special Offer: Buy 2, Get 1 Free!",
        "New Arrivals: Summer Collection"
    };

    // Экспорт в JSON
    std::cout << "=== JSON Export ===\n";
    JsonExportHandler jsonHandler;
    jsonHandler.processAndExport(rawData);

    // Экспорт в CSV
    std::cout << "\n=== CSV Export ===\n";
    CsvExportHandler csvHandler;
    csvHandler.processAndExport(rawData);
}