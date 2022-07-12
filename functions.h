#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace sf;

class Cialo : public Drawable {
public:
    RectangleShape cialo;
    int x, y;
    bool stan;

    Cialo();

    virtual void draw(RenderTarget& target, RenderStates states) const {
        target.draw(cialo);
    }
};

class Siatka : public Drawable {
public:
    VertexArray linia;
    float X, Y;

    Siatka();

    virtual void draw(RenderTarget& target, RenderStates states) const {
        target.draw(linia);
    }
};

std::string zamien(float i);

int rysujY(int y, Siatka *poziome, int liniePoziome);

int rysujX(int x, Siatka *pionowe, int liniePoziome);

struct sygnal {
    int strona;
    bool czyZwrot;
};

