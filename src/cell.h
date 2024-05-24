#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>

class Cell
{
    public:
        Cell(float x, float y, sf::Texture flagTexture);
        bool click();
        bool flag();
        sf::RectangleShape shape;

    private:
        const float size = 60;
        bool clicked;
        bool flagged;
        sf::Texture flagTexture;
    };

#endif