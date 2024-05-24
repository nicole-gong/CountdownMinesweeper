#include "main.h"
#include "cell.h"

int main() {
    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile("C:\\Users\\nicol\\Personal Projects\\Minesweeper\\src\\flag.png"))
        return -1;

    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Timed Minesweeper" };
    window.setFramerateLimit(60);

    std::vector<Cell> cells;
    cells.reserve(rows * cols);

    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            cells.emplace_back(i * size, j * size, flagTexture);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                for (auto &cell : cells)
                    if (cell.shape.getGlobalBounds().contains(mousePos)) 
                        cell.click();
            }

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                for (auto &cell : cells)
                    if (cell.shape.getGlobalBounds().contains(mousePos))
                        cell.flag();
            }
        }

        for (auto &cell : cells)
            window.draw(cell.shape);

        window.display();
    }
    return 0;
}