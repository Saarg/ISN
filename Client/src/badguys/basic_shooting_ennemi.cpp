#include "../../include/badguys/basic_shooting_ennemi.h"

basic_shooting_ennemi::basic_shooting_ennemi(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab):basic_ennemi(p_mslist, p_entity_tab)
{
     m_shootFreq = sf::seconds(0.9f);
     //m_mainShape->setFillColor(sf::Color::Red);
     m_mainShape = new sf::CircleShape(10.f);
     m_speed = sf::Vector2f(0, 2);
}

void basic_shooting_ennemi::Shoot()
{
    if(m_clock.getElapsedTime() > m_shootFreq)
    {
        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(m_mainShape->getPosition().x+10, m_mainShape->getPosition().y+20), sf::Vector2f(3,10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(m_mainShape->getPosition().x+10, m_mainShape->getPosition().y+20), sf::Vector2f(-3,10)));

        m_clock.restart();
    }
}
