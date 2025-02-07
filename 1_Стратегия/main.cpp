#include <iostream>
#include <vector>
class Glyph {
    public:
        virtual void Draw() = 0;
        virtual ~Glyph() = default;
};

class Compositor {
    public:
        virtual void Compose() = 0;
        virtual ~Compositor() = default;

};

class ArrayCompositor : public Compositor {
    public:
        void Compose() override {
            std::cout << "ArrayCompositor makes some changes!";
        }
};

class TeXCompositor : public Compositor{
    public:
        void Compose() override {
            std::cout << "TeXCompositor makes some changes!";
        }
};

class SimpleCompositor : public Compositor {
    public:
        void Compose() override {
            std::cout << "SimpleCompositor makes some changes!";
        }
};

class Composition {
    private:
        Compositor * compositor;
        std::vector<Glyph*> glyphs;
    
    public:
        Composition(Compositor * c) : compositor(c){}

        void addGlyph(Glyph*glyph) {
            glyphs.push_back(glyph);
        }

        void Draw() {
            for (auto glyph: glyphs){
                glyph->Draw();
            }
            compositor->Compose();
        }

        void setCompositor(Compositor*c) {
            compositor = c;
        }

        ~Composition() {
            for (auto glyph : glyphs){
                delete glyph;
            }
        }
};

class CircleGlyph : public Glyph {
public:
    void Draw() override {
        std::cout << "Drawing a circle." << std::endl;
    }
};

class SquareGlyph : public Glyph {
public:
    void Draw() override {
        std::cout << "Drawing a square." << std::endl;
    }
};





int main() {

    SimpleCompositor simpleCompositor;

    Composition composition(&simpleCompositor);

    composition.addGlyph(new CircleGlyph());
    composition.addGlyph(new SquareGlyph());
.
    composition.Draw();

    ArrayCompositor arrayCompositor;
    composition.setCompositor(&arrayCompositor);
    
    composition.Draw();

    std::cout << "\n";


    return 0;
}