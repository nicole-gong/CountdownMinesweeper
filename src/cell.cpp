#include "cell.h"

Cell::Cell(int x, int y, sf::Texture &flagTexture, sf::Font &font) : flagTexture(flagTexture), font(font), mineCount(0), clicked(false), flagged(false), x_coord(x), y_coord(y)
{
    shape.setSize({size, size});
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1);

    mineText.setFont(font);
    mineText.setCharacterSize(20);
    mineText.setFillColor(sf::Color::Black);
    mineText.setPosition(x + 5, y + 5);
}

bool Cell::click() {
    if (!flagged)
        if (!clicked) {
            clicked = true;
            return true;
        }
    return false;
}

bool Cell::flag() {
    if (!clicked)
    {
        flagged = !flagged;
        if (flagged) {
            shape.setTexture(&flagTexture);
            return true;
        }
        else 
            shape.setTexture(NULL);
    }
    return false;
}

void Cell::update() {
    if (mineCount > 0)
        mineText.setString(std::to_string(mineCount));

    shape.setFillColor(sf::Color::Green);
}