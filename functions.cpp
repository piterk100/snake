#include <SFML/Graphics.hpp>
#include "functions.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace sf;

Cialo::Cialo() {
    stan = 0;
    x = rand()%40*20+10;
    y = rand()%30*20+10;
    cialo.setSize(Vector2f(20, 20));
    cialo.setOrigin(10, 10);
    cialo.setFillColor(Color::Red);
    cialo.setPosition(x, y);
}

Siatka::Siatka() {
    linia = VertexArray(Lines, 2);
    linia[0].position = Vector2f(20, 0);
    linia[1].position = Vector2f(20, 600);
    linia[0].color = Color::Blue;
    linia[1].color = Color::Blue;
}

std::string zamien(float i) {
    std::stringstream ss;
    ss << i;
    std::string zamienione = ss.str();
    return zamienione;
}

int rysujY(int y, Siatka *poziome, int liniePoziome) {
    for(int i = 0; i < liniePoziome; i++) {
        poziome[i].linia[0].position = Vector2f(0, y);
        poziome[i].linia[1].position = Vector2f(800, y);
        y += 20;
    }
    return y;
}

int rysujX(int x, Siatka *pionowe, int liniePionowe) {
    for(int i = 0; i < liniePionowe; i++) {
        pionowe[i].linia[0].position = Vector2f(x, 0);
        pionowe[i].linia[1].position = Vector2f(x, 600);
        x += 20;
    }
    return x;
}
