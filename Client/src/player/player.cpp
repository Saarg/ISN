#include "../../include/player/player.h"

player::player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab): vaisseau(p_mslist, p_entity_tab)
{
    m_shootFreq = sf::seconds(0.3f);
    m_mainShape->setPosition(sf::Vector2f(400, 650));
}

player::~player()
{
    //dtor
}

void player::Shoot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and m_clock.getElapsedTime() > m_shootFreq)
    {
        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(5,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(0,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-5,-10)));

        m_clock.restart();
    }
}

void player::Move()
{
    m_mainShape->move(m_speed);
}

void player::onHit(float degat)
{

}
