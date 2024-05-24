#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>

class Cell
{
    public:
        Cell(float x, float y, sf::Texture flagTexture);

        void click();
        void flag();
        sf::RectangleShape shape;
        const float size = 60;

    private:
        bool clicked;
        bool flagged;
        sf::Texture flagTexture;
    };

#endif