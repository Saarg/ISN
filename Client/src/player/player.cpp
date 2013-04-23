#include "../../include/player/player.h"

player::player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab): vaisseau(p_mslist, p_entity_tab)
{
    m_shootFreq = sf::seconds(0.3f);
    m_mainShape->setFillColor(sf::Color(100,200,200));
    m_mainShape->setPosition(sf::Vector2f(400, 650));
    m_scoreR = 0;
    m_scoreG = 0;
    m_scoreB = 0;
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
    if(((m_bonus_score >= 20 and m_bonus_score < 40) or m_bonus_score >= 60) and sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(2,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(0,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-2,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(4,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-4,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(6,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-6,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(8,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-8,-10)));

         m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(10,-10)));

        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(-10,-10)));



    }
    if(m_bonus_score >= 40 and m_shootFreq != sf::seconds(0.1f) and sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //clockSpeed(0.1f);

    }
}

void player::Move()
{
    m_mainShape->move(m_speed);
}

void player::onHit(float degat)
{

}
