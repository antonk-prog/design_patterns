#include <iostream>

class Glyph{
    public:
        virtual void Draw() = 0;
        virtual ~Glyph() = default;
};

class MonoGlyph : public Glyph {
    public:
        virtual void Draw() override{
           std::cout << "Drawing MonoGlyph" << std::endl; 
        }
};


class Border : public Glyph {
    private:
        Glyph * component;

    public:
        Border(Glyph*comp) : component(comp){}

        void Draw() override {
            component->Draw();
            DrawBorder();
        }

        void DrawBorder()  {
            std::cout << "Drawing Border" << std::endl;
        }

        ~Border() {
            delete component; 
        }
};

class Scroller : public Glyph {
private:
    Glyph* component;
public:
    Scroller(Glyph* comp) : component(comp) {}

    void Draw() override {
        component->Draw();
        
        std::cout << "Drawing Scroller" << std::endl;
    }

    ~Scroller() {
        delete component;
    }
};


int main() {

    Glyph * monoGlyph = new MonoGlyph();

    Glyph * borderGlyph = new Border(monoGlyph);

    Glyph * scrollerGlyph = new Scroller(borderGlyph);

    scrollerGlyph->Draw();

    delete scrollerGlyph;

    return 0;
}