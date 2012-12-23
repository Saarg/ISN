#include "../../include/badguys/basic_shooting_ennemi.h"

basic_shooting_ennemi::basic_shooting_ennemi()
{
     m_shootFreq = sf::seconds(0.9f);
     m_shootTime = 0;
     //m_mainShape->setFillColor(sf::Color::Red);
     m_mainShape = new sf::CircleShape(10.f);
}

void basic_shooting_ennemi::Shoot()
{
    if(m_shootTime > 60)//frequence de tir = 20/60 = 0.3s
    {
        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(m_mainShape->getPosition().x+10, m_mainShape->getPosition().y+10), sf::Vector2f(5,10)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(m_mainShape->getPosition().x+10, m_mainShape->getPosition().y+10), sf::Vector2f(0,10)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(m_mainShape->getPosition().x+10, m_mainShape->getPosition().y+10), sf::Vector2f(-5,10)));
        m_nbr_msl++;

        m_shootTime = 0;
    }
    else{m_shootTime++;}
}

void basic_shooting_ennemi::Move()
{
    m_mainShape->move(sf::Vector2f(0, 2));
}
