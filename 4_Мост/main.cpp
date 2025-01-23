#include <iostream>
#include <memory>

class Glyph {
public:
    virtual void Draw() = 0;
    virtual ~Glyph() = default;
};

class WindowImp {
public:
    virtual void DeviceRaise() = 0;
    virtual void DeviceRect(int x0, int y0, int x1, int y1) = 0;
    virtual ~WindowImp() = default;
};

class XWindowImp : public WindowImp {
public:
    void DeviceRaise() override {
        std::cout << "XWindowImp: Raising window" << std::endl;
    }

    void DeviceRect(int x0, int y0, int x1, int y1) override {
        std::cout << "XWindowImp: Drawing rectangle from (" << x0 << ", " << y0
                  << ") to (" << x1 << ", " << y1 << ")" << std::endl;
    }
};

class PMWindowImp : public WindowImp {
public:
    void DeviceRaise() override {
        std::cout << "PMWindowImp: Raising window" << std::endl;
    }

    void DeviceRect(int x0, int y0, int x1, int y1) override {
        std::cout << "PMWindowImp: Drawing rectangle from (" << x0 << ", " << y0
                  << ") to (" << x1 << ", " << y1 << ")" << std::endl;
    }
};

class MacWindowImp : public WindowImp {
public:
    void DeviceRaise() override {
        std::cout << "MacWindowImp: Raising window" << std::endl;
    }

    void DeviceRect(int x0, int y0, int x1, int y1) override {
        std::cout << "MacWindowImp: Drawing rectangle from (" << x0 << ", " << y0
                  << ") to (" << x1 << ", " << y1 << ")" << std::endl;
    }
};

class Window {
protected:
    std::unique_ptr<WindowImp> imp; 

public:
    Window(std::unique_ptr<WindowImp> imp) : imp(std::move(imp)) {}

    virtual void Raise() {
        imp->DeviceRaise();
    }

    virtual void DrawRect(int x0, int y0, int x1, int y1) {
        imp->DeviceRect(x0, y0, x1, y1);
    }

    virtual ~Window() = default;
};

class ApplicationWindow : public Window {
public:
    ApplicationWindow(std::unique_ptr<WindowImp> imp) : Window(std::move(imp)) {}

    void Iconify() {
        std::cout << "ApplicationWindow: Iconifying window" << std::endl;
    }
};

class IconWindow : public Window {
public:
    IconWindow(std::unique_ptr<WindowImp> imp) : Window(std::move(imp)) {}

    void DrawBorder() {
        std::cout << "IconWindow: Drawing border" << std::endl;
        DrawRect(0, 0, 100, 100); 
    }
};

class DialogWindow : public Window {
private:
    Window* owner; 

public:
    DialogWindow(std::unique_ptr<WindowImp> imp, Window* owner)
        : Window(std::move(imp)), owner(owner) {}

    void Lower() {
        std::cout << "DialogWindow: Lowering window" << std::endl;
        if (owner) {
            owner->Raise();
        }
    }

    void Draw() {
        std::cout << "DialogWindow: Drawing window" << std::endl;
        DrawRect(50, 50, 150, 150);
    }
};

int main() {
    std::unique_ptr<WindowImp> xImp = std::make_unique<XWindowImp>();
    std::unique_ptr<WindowImp> pmImp = std::make_unique<PMWindowImp>();
    std::unique_ptr<WindowImp> macImp = std::make_unique<MacWindowImp>();

    ApplicationWindow appWindow(std::move(xImp));
    IconWindow iconWindow(std::move(pmImp));
    DialogWindow dialogWindow(std::move(macImp), &appWindow);

    appWindow.Raise();
    appWindow.DrawRect(10, 10, 200, 200);
    appWindow.Iconify();

    iconWindow.DrawBorder();

    dialogWindow.Lower();
    dialogWindow.Draw();

    return 0;
}