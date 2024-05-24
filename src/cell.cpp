#include "cell.h"

Cell::Cell(float x, float y, sf::Texture flagTexture) : flagTexture(flagTexture), clicked(false), flagged(false)
{
    shape.setSize({size, size});
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1);
}

bool Cell::click()
{
    if (!flagged)
        if (!clicked) {
            clicked = true;
            shape.setFillColor(sf::Color::Green);
            return true;
        }
    return false;
}

bool Cell::flag()
{
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