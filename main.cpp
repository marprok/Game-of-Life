#include <iostream>
#include <vector>
#include <utility>
#include "Graphics.hpp"
#include "Cell.h"

constexpr int WIDTH = 500, HEIGHT = 300, CELL_DIM = 10, NUM_CELLS_X = WIDTH/CELL_DIM, NUM_CELLS_Y = HEIGHT/CELL_DIM;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Conway's Game of Life", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(10);

    std::vector<std::vector<Cell>> cells;
    cells.resize(NUM_CELLS_Y);

    // Populate the grid of cells.
    for (int i = 0; i < NUM_CELLS_Y; ++i)
        for (int j = 0; j < NUM_CELLS_X; ++j)
           cells[i].push_back(Cell(sf::Vector2f((float)CELL_DIM,(float)CELL_DIM), sf::Vector2f(j*((float)CELL_DIM),i*((float)CELL_DIM)), false));

    bool start = false;

    while (window.isOpen())
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
            {
                start = !start;
            }
            else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left)
            {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    // Find in which pixel we are closer to.
                    pos.x = (pos.x/CELL_DIM);
                    pos.y = (pos.y/CELL_DIM);
                    if (!cells[pos.y][pos.x].alive())
                        cells[pos.y][pos.x].resurrect();
                    else
                        cells[pos.y][pos.x].kill();
            }
        }

        window.clear();

        std::vector<std::pair<int,int>> dead;
        std::vector<std::pair<int,int>> alive;

        for (int i = 0; i < NUM_CELLS_Y; ++i)
        {
            for (int j = 0; j < NUM_CELLS_X; ++j)
            {
                if (start)
                {
                    int neighbours = 0;
                    for (int  y = -1; y <= 1; ++y)
                    {
                        for (int  x = -1; x <= 1; ++x)
                        {
                            if (i + y < cells.size() && i + y >= 0 && j + x < cells[i].size() && j + x >= 0)
                            {
                                if (cells[i + y][j + x].alive())
                                    neighbours++;
                            }
                        }
                    }
                    if (cells[i][j].alive())
                    {
                        // Remove the cell from the count.
                        neighbours--;
                        switch (neighbours)
                        {
                        case 0:case 1:
                            dead.push_back(std::pair<int,int>(i,j));
                            break;
                        case 2:case 3:
                            alive.push_back(std::pair<int,int>(i,j));
                            break;
                        case 4: case 5: case 6: case 7: case 8:
                            dead.push_back(std::pair<int,int>(i,j));
                            break;
                        }
                    }else
                        if (neighbours == 3)
                            alive.push_back(std::pair<int,int>(i,j));
                }
            }
        }

        for (auto& pos : dead)
            cells[pos.first][pos.second].kill();

        for (auto& pos : alive)
            cells[pos.first][pos.second].resurrect();

        for (int i = 0; i < NUM_CELLS_Y; ++i)
            for (int j = 0; j < NUM_CELLS_X; ++j)
                cells[i][j].draw(window);

        window.display();
    }

    return 0;
}
