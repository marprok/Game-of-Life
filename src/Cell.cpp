#include "Cell.h"

Cell::Cell(sf::Vector2f s, sf::Vector2f p, bool a)
:m_size(s), m_pos(p), m_alive(a)
{
    m_rect.setPosition(m_pos);
    m_rect.setOutlineColor(sf::Color::Black);
    m_rect.setSize(m_size);
}

void Cell::draw(sf::RenderWindow& window)
{
    if (m_alive)
        m_rect.setFillColor(sf::Color::Black);
    else
        m_rect.setFillColor(sf::Color::White);

    window.draw(m_rect);
}

bool Cell::alive()
{
    return m_alive;
}

void Cell::kill()
{
    m_alive = false;
}

void Cell::resurrect()
{
    m_alive = true;
}
