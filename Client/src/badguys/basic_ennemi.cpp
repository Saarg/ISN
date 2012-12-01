#include "../../include/badguys/basic_ennemi.h"

void basic_ennemi::Shoot(sf::RenderWindow* p_window)
{

}

void basic_ennemi::Move()
{
    m_mainShape->move(sf::Vector2f(0, 1));
}

void basic_ennemi::onHit(float degat)
{

}
