#ifndef CELL_H
#define CELL_H

#include "Graphics.hpp"


class Cell
{
    public:
        Cell(sf::Vector2f s, sf::Vector2f p, bool a = false);
        void draw(sf::RenderWindow& window);
        bool alive();
        void kill();
        void resurrect();
    private:
        sf::RectangleShape m_rect;
        sf::Vector2f m_size, m_pos;
        bool m_alive;

};

#endif // CELL_H
