#ifndef CELL_H
#define CELL_H
#include <SFML/Graphics.hpp>

class Cell
{
    public:
        Cell(int x, int y, sf::Texture &flagTexture, sf::Font &font);
        bool click();
        bool flag();
        void update();
        sf::RectangleShape shape;
        int mineCount;
        const int x_coord;
        const int y_coord;
        sf::Text mineText;

    private:
        const float size = 60;
        bool clicked;
        bool flagged;
        const sf::Texture flagTexture;
        const sf::Font font;
    };

#endif