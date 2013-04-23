#include "../include/vaisseau.h"

vaisseau::vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab)
{
    m_msList = p_mslist;
    m_entity_tab = p_entity_tab;
    m_mainShape = new sf::RectangleShape(sf::Vector2f(20, 20));

    if (!m_texture.loadFromFile("ressources/carac/vaisseau.png"))
        std::cout << "ressources/carac/vaisseau.png introuvable" << std::endl;

    m_mainShape->setTexture(&m_texture);

    m_mainShape->setFillColor(sf::Color::Red);
    m_mainShape->setPosition(sf::Vector2f(200, 0));

    m_clock.restart();
    m_shootFreq = sf::seconds(0.5f);

    m_speed = sf::Vector2f(0, 0);
    m_life = 100;
    m_bonus_score=0;
}

vaisseau::~vaisseau()
{

}

void vaisseau::setPosition(sf::Vector2f position)
{
    m_mainShape->setPosition(position);
}

void vaisseau::setPosition(int x, int y)
{
    m_mainShape->setPosition(x, y);
}

void vaisseau::setPosition(float x, float y)
{
    m_mainShape->setPosition(x, y);
}

sf::Vector2f vaisseau::getPosition()
{
    return m_mainShape->getPosition();
}

void vaisseau::setColor(sf::Color color)
{
    m_mainShape->setFillColor(color);
}

sf::Color vaisseau::getColor()
{
    return m_mainShape->getFillColor();

}

bool vaisseau::isAlive()
{
    if(m_life <= 0)
        return false;
    else
        return true;
}

void vaisseau::Shoot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and !(getPosition().x < 5 or getPosition().x > 795 or getPosition().y < 600 or getPosition().y > 900)
            and m_clock.getElapsedTime() > m_shootFreq)
    {
        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y), sf::Vector2f(0,-10)));

        m_clock.restart();
    }
}

void vaisseau::Move()
{
    sf::Time time = m_clock2.restart();
    m_mainShape->move(m_speed*(time.asSeconds()*60));
}

void vaisseau::onHit(float degat)
{
    m_life -= degat;
}

void vaisseau::changeScore(sf::Color c1, sf::Color c2, sf::Vector2f size)
{
    m_scoreR = m_scoreR + abs(c1.r-c2.r)*(size.x/5);
    m_scoreG = m_scoreG + abs(c1.g-c2.g)*(size.x/5);
    m_scoreB = m_scoreB + abs(c1.b-c2.b)*(size.x/5);
}

void vaisseau::Draw(sf::RenderWindow* p_window)
{
    Move();
    Shoot();
    p_window->draw(*m_mainShape);

    if(m_life <= 0)
    {
        for(std::vector<vaisseau*>::size_type j = 0 ; j < m_entity_tab->size() ; j++)
        {
            if(m_entity_tab->at(j)->getPosition() == getPosition())
                m_entity_tab->erase(m_entity_tab->begin()+j);
        }
    }
}
