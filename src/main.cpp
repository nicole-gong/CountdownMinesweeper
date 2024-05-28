#include "main.h"
#include "cell.h"
#include "timer.h"
using namespace std;
#include <iostream>

// thanks gpt
void generateMines (vector<vector<bool>> &mineGrid, int firstRow, int firstCol)
{
    int minesPlaced = 0;
    srand(static_cast<unsigned int>(time(NULL)));
    auto distance = [firstRow, firstCol](int i, int j)
    { return sqrt(pow(i - firstRow, 2) + pow(j - firstCol, 2)); };

    while (minesPlaced < NUM_MINES)
    {
        int i = rand() % ROWS;
        int j = rand() % COLS;
        double dist = distance(i, j);

        double probability = exp(-dist / 3); 

        if (static_cast<double>(rand()) / RAND_MAX < probability && !mineGrid[i][j] && (i != firstRow && j != firstCol))
        {
            mineGrid[i][j] = true;
            minesPlaced++;
        }
    }
}

void countMines(vector<vector<bool>> &mineGrid, Cell &cell) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int row = cell.y_coord / CELL_SIZE + i;
            int col = cell.x_coord / CELL_SIZE + j;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS && !(i == 0 && j == 0) && mineGrid[row][col])
                count++;
        }
    }
    cell.mineCount = count;
}

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

    vector<vector<bool>> mineGrid(ROWS, vector<bool>(COLS, false));
    vector<Cell> cells;
    cells.reserve(ROWS * COLS);

    for (int i = 0; i < ROWS; i++) 
        for (int j = 0; j < COLS; j++) 
            cells.emplace_back(j * CELL_SIZE, i * CELL_SIZE, flagTexture, font);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameAlive) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (auto &cell : cells)
                        if (cell.shape.getGlobalBounds().contains(mousePos))
                        {
                            if (cell.click())
                            {
                                if (mineGrid[int(mousePos.y / CELL_SIZE)][int(mousePos.x / CELL_SIZE)])
                                    gameAlive = false;
                                if (!timer.running) {
                                    generateMines(mineGrid, int(mousePos.x / CELL_SIZE), int(mousePos.y / CELL_SIZE));
                                    for (auto &cell : cells) 
                                        countMines(mineGrid, cell);

                                    for (int i = 0; i < ROWS; i++)
                                    {
                                        for (int j = 0; j < COLS; j++)
                                        {
                                            cout << mineGrid[i][j] << " ";
                                        }
                                        cout << endl;
                                    }

                                    timer.start();
                                }
                                else
                                    timer.reset(currFlags);

                                // cout << int(mousePos.x / CELL_SIZE) << " " << int(mousePos.y / CELL_SIZE) << endl;

                                if (gameAlive) 
                                    cell.update();
                                else
                                    cell.shape.setFillColor(sf::Color::Red);
                            }
                        }
                }

                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    for (auto &cell : cells)
                        if (cell.shape.getGlobalBounds().contains(mousePos))
                        {
                            if (cell.flag())
                                currFlags += 1;
                            else
                                currFlags -= 1;
                        }
                }
            }
        }

        if (timer.getRemaining().asSeconds() < 0)
            gameAlive = false;
        
        if (gameAlive)
            text.setString(std::to_string(timer.getRemaining().asSeconds()));
        else
            text.setString("My life is like a video game\n"
                           "Trying hard to beat the stage\n"
                           "All while I am still collecting coins\n"
                           "Trying hard to save the girl\n"
                           "Obstacles, I'm jumping hurdles\n"
                           "I'm growing up to be a big boy");

        for (auto &cell : cells) {
            window.draw(cell.shape);
            window.draw(cell.mineText);
        }
        window.draw(text);
        window.display();
    }
    return 0;
}