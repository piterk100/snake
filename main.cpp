#include <SFML/Graphics.hpp>
#include "functions.h"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace sf;

int main() {
    RenderWindow okno(VideoMode(800, 600), "Snake");

    srand(time(NULL));

    int liniePoziome = 29;
    Siatka *poziome = new Siatka[liniePoziome];
    int y = rysujY(20, poziome, liniePoziome);

    int liniePionowe = 39;
    Siatka *pionowe = new Siatka[liniePionowe];
    int x = rysujX(20, pionowe, liniePionowe);

    Cialo glowa;
    float X = 0;
    float Y = 0;
    glowa.cialo.setFillColor(Color::Green);
    glowa.cialo.setPosition(390, 290);
    glowa.stan = 1;

    int limitCial = 100;
    Cialo *cialo = new Cialo[limitCial];
    int ileCial = 0;
    bool czyNowy = 0;
    float wx[limitCial];
    float wy[limitCial];

    int strona = 1;
    int kolejne[100];
    kolejne[0] = 20;
    for(int i = 1; i < 100; i++)
        kolejne[i] = kolejne[i-1] + 20;

    int limitZwrotow = 500;

    Vector2f **zwroty;
    zwroty = new Vector2f*[limitZwrotow];
    for(int i = 0; i < limitCial; i++)
        zwroty[i] = new Vector2f[limitCial];

    int **stronaZwrotu;
    stronaZwrotu = new int*[limitZwrotow];
    for(int i = 0; i < limitCial; i++)
        stronaZwrotu[i] = new int[limitCial];

    int ileZwrotow[1000];
    for(int i = 0; i < 1000; i++)
        ileZwrotow[i] = 0;

    bool czyZwrot = 0;
    bool koniec = 0;

    Font font;
    font.loadFromFile("arial-narrow.ttf");

    Text gameOver;
    gameOver.setString("KONIEC GRY!");
    gameOver.setFont(font);
    gameOver.setColor(Color::White);
    gameOver.setCharacterSize(100);
    gameOver.setPosition(140, 60);

    Text punkty;
    punkty.setFont(font);
    punkty.setColor(Color::White);
    punkty.setCharacterSize(50);
    punkty.setPosition(300, 200);

    while(okno.isOpen()) {
        Event zdarzenie;
        while(okno.pollEvent(zdarzenie)) {
            if(zdarzenie.type == Event::Closed)
                okno.close();

            if(zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape)
                okno.close();

            if(zdarzenie.type == Event::MouseButtonPressed && zdarzenie.mouseButton.button == Mouse::Middle)
                okno.close();

            if (zdarzenie.type == Event::Resized) {
                FloatRect visibleArea(0, 0, zdarzenie.size.width, zdarzenie.size.height);
                okno.setView(View(visibleArea));
            }
        }

        float pozx = glowa.cialo.getPosition().x;
        int pozX = int(pozx);
        float pozy = glowa.cialo.getPosition().y;
        int pozY = int(pozy);

        if(Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && strona != 2 && strona != 1) {
            strona = 1;
            czyZwrot = 1;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && strona != 1 && strona != 2) {
            strona = 2;
            czyZwrot = 1;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left) && !Keyboard::isKeyPressed(Keyboard::Right) && strona != 3 && strona != 4) {
            strona = 4;
            czyZwrot = 1;
        }
        else if(!Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Right) && strona != 4 && strona != 3) {
            strona = 3;
            czyZwrot = 1;
        }

        if(strona == 1 && pozX%10 == 0 && pozX%20 != 0 && pozY%10 == 0 && pozY%20 != 0 && czyZwrot == 1) {
            X = 0;
            Y = -0.25;
            if(ileCial > 1) {
                for(int i = 0; i < ileCial - 1; i++) {
                    zwroty[i][ileZwrotow[i]] = glowa.cialo.getPosition();
                    stronaZwrotu[i][ileZwrotow[i]] = strona;
                }
                for(int i = 0; i < ileCial - 1; i++)
                    ileZwrotow[i]++;
            }
            czyZwrot = 0;
        }
        else if(strona == 2 && pozX%10 == 0 && pozX%20 != 0 && pozY%10 == 0 && pozY%20 != 0 && czyZwrot == 1) {
            X = 0;
            Y = 0.25;
            if(ileCial > 1) {
                for(int i = 0; i < ileCial - 1; i++) {
                    zwroty[i][ileZwrotow[i]] = glowa.cialo.getPosition();
                    stronaZwrotu[i][ileZwrotow[i]] = strona;
                }
                for(int i = 0; i < ileCial - 1; i++)
                    ileZwrotow[i]++;
            }
            czyZwrot = 0;
        }
        else if(strona == 3 && pozY%10 == 0 && pozY%20 != 0 && pozY%10 == 0 && pozY%20 != 0 && czyZwrot == 1) {
            X = 0.25;
            Y = 0;
            if(ileCial > 1) {
                for(int i = 0; i < ileCial - 1; i++) {
                    zwroty[i][ileZwrotow[i]] = glowa.cialo.getPosition();
                    stronaZwrotu[i][ileZwrotow[i]] = strona;
                }
                for(int i = 0; i < ileCial - 1; i++)
                    ileZwrotow[i]++;
            }
            czyZwrot = 0;
        }
        else if(strona == 4 && pozY%10 == 0 && pozY%20 != 0 && pozY%10 == 0 && pozY%20 != 0 && czyZwrot == 1) {
            X = -0.25;
            Y = 0;
            if(ileCial > 1) {
                for(int i = 0; i < ileCial - 1; i++) {
                    zwroty[i][ileZwrotow[i]] = glowa.cialo.getPosition();
                    stronaZwrotu[i][ileZwrotow[i]] = strona;
                }
                for(int i = 0; i < ileCial - 1; i++)
                    ileZwrotow[i]++;
            }
            czyZwrot = 0;
        }

        if(koniec == 0)
            glowa.cialo.move(X, Y);

        if(czyNowy == 0 && ileCial < limitCial) {
            cialo[ileCial];
            czyNowy = 1;
            ileCial++;
        }

        if(((glowa.cialo.getPosition().x - cialo[ileCial-1].cialo.getPosition().x) < 10 && (glowa.cialo.getPosition().x - cialo[ileCial-1].cialo.getPosition().x) > -10) &&
                ((glowa.cialo.getPosition().y - cialo[ileCial-1].cialo.getPosition().y) < 10 && (glowa.cialo.getPosition().y - cialo[ileCial-1].cialo.getPosition().y > -10))) {
            cialo[ileCial-1].cialo.setFillColor(Color::Green);
            cialo[ileCial-1].stan = 1;
            czyNowy = 0;

            wx[ileCial-1] = X;
            wy[ileCial-1] = Y;

            if(strona == 1)
                cialo[ileCial-1].cialo.setPosition(glowa.cialo.getPosition().x, glowa.cialo.getPosition().y+kolejne[ileCial-1]);

            else if(strona == 2)
                cialo[ileCial-1].cialo.setPosition(glowa.cialo.getPosition().x, glowa.cialo.getPosition().y-kolejne[ileCial-1]);

            else if(strona == 3)
                cialo[ileCial-1].cialo.setPosition(glowa.cialo.getPosition().x-kolejne[ileCial-1], glowa.cialo.getPosition().y);

            else if(strona == 4)
                cialo[ileCial-1].cialo.setPosition(glowa.cialo.getPosition().x+kolejne[ileCial-1], glowa.cialo.getPosition().y);
        }

        for(int i = 0; i < ileCial - 1; i++) {
            if(cialo[i].stan == 1 && cialo[i].cialo.getPosition() == zwroty[i][0]) {
                if(stronaZwrotu[i][0] == 1) {
                    wx[i] = 0;
                    wy[i] = -0.25;
                }
                else if(stronaZwrotu[i][0] == 2) {
                    wx[i] = 0;
                    wy[i] = 0.25;
                }
                else if(stronaZwrotu[i][0] == 3) {
                    wx[i] = 0.25;
                    wy[i] = 0;
                }
                else if(stronaZwrotu[i][0] == 4) {
                    wx[i] = -0.25;
                    wy[i] = 0;
                }

                for(int j = 1; j < ileZwrotow[i]; j++) {
                    zwroty[i][j-1] = zwroty[i][j];
                    stronaZwrotu[i][j-1] = stronaZwrotu[i][j];
                }
                ileZwrotow[i]--;
            }
        }

        for(int i = 0; i < ileCial - 1; i++)
            if(cialo[i].stan == 1 && koniec == 0)
                cialo[i].cialo.move(wx[i], wy[i]);

        for(int i = 1; i < ileCial - 1; i++)
            if((glowa.cialo.getPosition().x - cialo[i].cialo.getPosition().x < 19 && glowa.cialo.getPosition().x - cialo[i].cialo.getPosition().x > -19) &&
                    (glowa.cialo.getPosition().y - cialo[i].cialo.getPosition().y < 19 && glowa.cialo.getPosition().y - cialo[i].cialo.getPosition().y > -19))
                koniec = 1;

        if(glowa.cialo.getPosition().x > 790 || glowa.cialo.getPosition().x < 10 || glowa.cialo.getPosition().y > 590 || glowa.cialo.getPosition().y < 10)
            koniec = 1;

        punkty.setString("Punkty: " + zamien(ileCial-1));

        okno.clear();

        for(int i = 0; i < 39; i++)
            okno.draw(pionowe[i]);

        for(int i = 0; i < 29; i++)
            okno.draw(poziome[i]);

        for(int i = 0; i < ileCial; i++)
            okno.draw(cialo[i]);

        okno.draw(glowa);

        if(koniec == 1) {
            okno.draw(gameOver);
            okno.draw(punkty);
        }

        okno.display();
    }
    delete [] poziome;
    delete [] pionowe;
    delete [] cialo;
    for(int i = 0; i < limitCial; i++) {
        delete [] zwroty[i];
        delete [] stronaZwrotu[i];
    }
    delete [] zwroty;
    delete [] stronaZwrotu;
    return 0;
}
