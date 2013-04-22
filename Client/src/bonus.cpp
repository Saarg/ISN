#include "../include/bonus.h"

Bonus::Bonus(sf::Vector2f position,sf::Color couleur1,sf::Color couleur2, int value)
{

  m_mainShape = new sf::RectangleShape(sf::Vector2f(10, 10));
  m_mainShape->setFillColor(couleur1);
  m_mainShape->setOutlineThickness(2);
  m_mainShape->setOutlineColor(couleur2);
  m_mainShape->setPosition(sf::Vector2f(position));
  m_speed = sf::Vector2f(0, 1);
  m_bonusValue = value;

}

Bonus::~Bonus()
{
    delete m_mainShape;
}
sf::Vector2f Bonus::getPosition()
{
    return m_mainShape->getPosition();
}
void Bonus::Move()
{
    sf::Time time = m_clock.restart();
    m_mainShape->move(m_speed*(time.asSeconds()*60));
}
void Bonus::Draw(sf::RenderWindow* p_window)
{
    Move();
    p_window->draw(*m_mainShape);
}
int Bonus::bonusVal()
{
    return m_bonusValue;
}

sf::Color Bonus::getFillColor()
{
    return m_mainShape->getFillColor();
}

sf::Color Bonus::getOutlineColor()
{
    return m_mainShape->getOutlineColor();
}

sf::Vector2f Bonus::getSize()
{
    return m_mainShape->getSize();
}
