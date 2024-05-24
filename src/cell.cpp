#include "cell.h"

Cell::Cell(float x, float y, sf::Texture flagTexture) : flagTexture(flagTexture), clicked(false), flagged(false)
{
    shape.setSize({size, size});
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(-1);
}

void Cell::click()
{
    if (!flagged)
    {
        clicked = true;
        shape.setFillColor(sf::Color::Green);
    }
}

void Cell::flag()
{
    if (!clicked)
    {
        flagged = !flagged;
        if (flagged)
            shape.setTexture(&flagTexture);
        else
            shape.setTexture(NULL);
    }
}