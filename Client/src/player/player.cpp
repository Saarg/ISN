#include "../../include/player/player.h"

player::player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab): vaisseau(p_mslist, p_entity_tab)
{
    m_shootFreq = sf::seconds(0.3f);

    if (!m_texture.loadFromFile("ressources/carac/player.png"))
        std::cout << "ressources/carac/player.png introuvable" << std::endl;

    m_mainShape->setTexture(&m_texture);

    m_mainShape->setFillColor(sf::Color(100,200,200));
    m_mainShape->setPosition(sf::Vector2f(400, 650));
    m_scoreR = 0;
    m_scoreG = 0;
    m_scoreB = 0;

    m_shots.push_back(sf::Vector2f(0, -10));
    m_shots.push_back(sf::Vector2f(3, -10));
    m_shots.push_back(sf::Vector2f(-3, -10));
}

player::~player()
{
    //dtor
}

void player::Shoot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and m_clock.getElapsedTime() > m_shootFreq)
    {
        for(std::vector<sf::Vector2f>::size_type i = 0 ; i < m_shots.size() ; i++)
        {
            m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getGlobalBound().left+getGlobalBound().width/2, getGlobalBound().top), m_shots[i]));
        }
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
