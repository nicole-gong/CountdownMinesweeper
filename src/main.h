#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>

class Cell {
    public:
        Cell(float x, float y, sf::Texture flagTexture);

        void click();
        void flag();
        void draw(sf::RenderWindow &window);
        sf::RectangleShape shape;

    private:
        bool clicked;
        bool flagged;
        sf::Texture flagTexture;
};

#endif