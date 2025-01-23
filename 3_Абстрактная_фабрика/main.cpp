#include <iostream>
#include <cstring>
class Glyph {
public:
    virtual ~Glyph() = default;
};
    
class ScrollBar : public Glyph {
public:
    virtual void ScrollTo(int position) = 0;
};

class Button : public Glyph {
public:
    virtual void Press() = 0;
};

class Menu : public Glyph {
public:
    virtual void Popup() = 0;
};

class MotifScrollBar : public ScrollBar {
public:
    void ScrollTo(int position) override {
        std::cout << "Motif ScrollBar scrolled to position " << position << std::endl;
    }
};

class MotifButton : public Button {
public:
    void Press() override {
        std::cout << "Motif Button pressed" << std::endl;
    }
};

class MotifMenu : public Menu {
public:
    void Popup() override {
        std::cout << "Motif Menu popped up" << std::endl;
    }
};

class PMScrollBar : public ScrollBar {
public:
    void ScrollTo(int position) override {
        std::cout << "PM ScrollBar scrolled to position " << position << std::endl;
    }
};

class PMButton : public Button {
public:
    void Press() override {
        std::cout << "PM Button pressed" << std::endl;
    }
};

class PMMenu : public Menu {
public:
    void Popup() override {
        std::cout << "PM Menu popped up" << std::endl;
    }
};

class MacScrollBar : public ScrollBar {
public:
    void ScrollTo(int position) override {
        std::cout << "Mac ScrollBar scrolled to position " << position << std::endl;
    }
};

class MacButton : public Button {
public:
    void Press() override {
        std::cout << "Mac Button pressed" << std::endl;
    }
};

class MacMenu : public Menu {
public:
    void Popup() override {
        std::cout << "Mac Menu popped up" << std::endl;
    }
};



class GUIFactory {
public:
    virtual ScrollBar* CreateScrollBar() = 0;
    virtual Button* CreateButton() = 0;
    virtual Menu* CreateMenu() = 0;
    virtual ~GUIFactory() = default;
};

class MotifFactory : public GUIFactory {
public:
    ScrollBar* CreateScrollBar() override {
        return new MotifScrollBar();
    }

    Button* CreateButton() override {
        return new MotifButton();
    }

    Menu* CreateMenu() override {
        return new MotifMenu();
    }
};

class PMFactory : public GUIFactory {
public:
    ScrollBar* CreateScrollBar() override {
        return new PMScrollBar();
    }

    Button* CreateButton() override {
        return new PMButton();
    }

    Menu* CreateMenu() override {
        return new PMMenu();
    }
};

class MacFactory : public GUIFactory {
public:
    ScrollBar* CreateScrollBar() override {
        return new MacScrollBar();
    }

    Button* CreateButton() override {
        return new MacButton();
    }

    Menu* CreateMenu() override {
        return new MacMenu();
    }
};

GUIFactory* CreateFactory(const char* styleName) {
    if (strcmp(styleName, "Motif") == 0) {
        return new MotifFactory();
    } else if (strcmp(styleName, "Presentation_Manager") == 0) {
        return new PMFactory();
    } else if (strcmp(styleName, "Mac") == 0) {
        return new MacFactory();
    } else {
        return nullptr; 
    }
}

int main() {
    const char* styleName = "Motif";
    GUIFactory* factory = CreateFactory(styleName);

    if (factory) {
        ScrollBar* scrollBar = factory->CreateScrollBar();
        Button* button = factory->CreateButton();
        Menu* menu = factory->CreateMenu();

        scrollBar->ScrollTo(10);
        button->Press();
        menu->Popup();

        delete scrollBar;
        delete button;
        delete menu;
        delete factory;
    } else {
        std::cout << "Unknown style" << std::endl;
    }

    return 0;
}