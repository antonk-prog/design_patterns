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

class WindowSystemFactory {
public:
    virtual WindowImp* CreateWindowImp() = 0;
    virtual ~WindowSystemFactory() = default;
};

class PWMindowSystemFactory : public WindowSystemFactory {
public:
    WindowImp* CreateWindowImp() override {
        return new PMWindowImp();
    }
};

class XWindowSystemFactory : public WindowSystemFactory {
public:
    WindowImp* CreateWindowImp() override {
        return new XWindowImp();
    }
};

class MacWindowSystemFactory : public WindowSystemFactory {
public:
    WindowImp* CreateWindowImp() override {
        return new MacWindowImp();
    }
};

class Window {
protected:
    std::unique_ptr<WindowImp> imp;

public:
    Window(WindowSystemFactory* factory) {
        imp.reset(factory->CreateWindowImp());
    }

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
    ApplicationWindow(WindowSystemFactory* factory) : Window(factory) {}

    void Iconify() {
        std::cout << "ApplicationWindow: Iconifying window" << std::endl;
    }
};

class IconWindow : public Window {
public:
    IconWindow(WindowSystemFactory* factory) : Window(factory) {}

    void DrawBorder() {
        std::cout << "IconWindow: Drawing border" << std::endl;
        DrawRect(0, 0, 100, 100);
    }
};

class DialogWindow : public Window {
private:
    Window* owner; 

public:
    DialogWindow(WindowSystemFactory* factory, Window* owner)
        : Window(factory), owner(owner) {}

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
    PWMindowSystemFactory pmFactory;
    XWindowSystemFactory xFactory;
    MacWindowSystemFactory macFactory;

    ApplicationWindow appWindow(&xFactory);
    IconWindow iconWindow(&pmFactory);
    DialogWindow dialogWindow(&macFactory, &appWindow);

    appWindow.Raise();
    appWindow.DrawRect(10, 10, 200, 200);
    appWindow.Iconify();

    iconWindow.DrawBorder();

    dialogWindow.Lower();
    dialogWindow.Draw();

    return 0;
}