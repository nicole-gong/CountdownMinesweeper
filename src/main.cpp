#include "main.h"
#include "cell.h"
#include "timer.h"

int main() {
    int currFlags = 0;
    sf::Texture flagTexture;
    if (!flagTexture.loadFromFile(absolutePath + "resources\\flag.png"))
        return -1;

    sf::Font font;
    if (!font.loadFromFile(absolutePath + "resources\\Consolas.ttf"))
        return -1;
    sf::Text text;
    text.setFont(font); 
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);

    bool gameAlive = true;

    Timer timer;
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Timed Minesweeper" };
    window.setFramerateLimit(30);

    std::vector<Cell> cells;
    cells.reserve(rows * cols);

    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            cells.emplace_back(i * cell_size, j * cell_size, flagTexture);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameAlive) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (auto &cell : cells)
                        if (cell.shape.getGlobalBounds().contains(mousePos)) {
                            if (cell.click()) {
                                if (!timer.running)
                                    timer.start();
                                else
                                    timer.reset(currFlags);
                            }
                        }
                }

                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (auto &cell : cells)
                        if (cell.shape.getGlobalBounds().contains(mousePos)) {
                            if (cell.flag()) 
                                currFlags += 1;
                            else 
                                currFlags -= 1;
                        }
                }
            }
        }

        if (timer.getRemaining().asSeconds() < 0)
        {
            gameAlive = false;
            text.setString("My life is like a video game\n" 
                        "Trying hard to beat the stage\n"
                        "All while I am still collecting coins\n"
                        "Trying hard to save the girl\n"
                        "Obstacles, I'm jumping hurdles\n"
                        "I'm growing up to be a big boy");
        }
        else
            text.setString(std::to_string(timer.getRemaining().asSeconds()));

        for (auto &cell : cells)
            window.draw(cell.shape);
        window.draw(text);
        window.display();
    }
    return 0;
}