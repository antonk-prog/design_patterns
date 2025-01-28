#include <iostream>
#include <string>

// Интерфейс, который реализуют как реальный объект, так и заместитель
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() = default;
};

// Реальный объект
class RealImage : public Image {
private:
    std::string filename;

    void loadFromDisk() {
        std::cout << "Loading image: " << filename << std::endl;
    }

public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }

    void display() override {
        std::cout << "Displaying image: " << filename << std::endl;
    }
};

// Заместитель
class ProxyImage : public Image {
private:
    std::string filename;
    RealImage* realImage;

public:
    ProxyImage(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() override {
        if (realImage == nullptr) {
            realImage = new RealImage(filename); // Ленивая загрузка
        }
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage;
    }
};

// Клиентский код
int main() {
    Image* image = new ProxyImage("test_image.jpg");

    // Изображение будет загружено только при вызове display()
    image->display();

    // Повторный вызов display() не загружает изображение снова
    image->display();

    delete image;
    return 0;
}