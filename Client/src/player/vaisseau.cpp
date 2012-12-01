#include "../../include/player/vaisseau.h"

vaisseau::vaisseau()
{
    m_mainShape = new sf::CircleShape(10.f);
    m_mainShape->setFillColor(sf::Color::Red);
    m_mainShape->setPosition(sf::Vector2f(10, 10));

    m_shootFreq = sf::seconds(0.2f);
    m_nbr_msl = 0;

    life = 100;
}

vaisseau::~vaisseau()
{
    //delete m_mainShape;
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

//setShapeOptions
void vaisseau::setColor(sf::Color color)
{
    m_mainShape->setFillColor(color);
}

void vaisseau::setAngle(float angle)
{
    m_mainShape->setRotation(angle);
}

sf::Vector2f vaisseau::getPosition()
{
    return m_mainShape->getPosition();
}

//getShapeOptions

sf::Color vaisseau::getColor()
{
    return m_mainShape->getFillColor();
}

float vaisseau::getAngle()
{
    return m_angle;
}

//mainFonctions
void vaisseau::Shoot(sf::RenderWindow* p_window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and sf::Mouse::getPosition(*p_window).x > 5 and sf::Mouse::getPosition(*p_window).x < 795 and sf::Mouse::getPosition(*p_window).y > 600 and sf::Mouse::getPosition(*p_window).y < 900
            and m_clock.getElapsedTime() >= m_shootFreq)
    {
        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(sf::Mouse::getPosition(*p_window).x-1, sf::Mouse::getPosition(*p_window).y-1), sf::Vector2f(2.5,-5)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(sf::Mouse::getPosition(*p_window).x-1, sf::Mouse::getPosition(*p_window).y-1), sf::Vector2f(0,-5)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(sf::Mouse::getPosition(*p_window).x-1, sf::Mouse::getPosition(*p_window).y-1), sf::Vector2f(-2.5,-5)));
        m_nbr_msl++;

        m_clock.restart();
    }
}

void vaisseau::Move()
{

}

void vaisseau::onHit(float degat)
{
    life -= degat;
}

void vaisseau::Draw(sf::RenderWindow* p_window)
{
    for(int i = 0 ; i < (int) (m_msList.size()) ; i++)
    {
        if(m_msList[i].getPosition().x < 0 or m_msList[i].getPosition().x > 800 or m_msList[i].getPosition().y < 0 or m_msList[i].getPosition().y > 900){
            m_msList.erase(m_msList.begin()+i);
        }else{
            m_msList[i].Move();
            m_msList[i].Draw(p_window);
        }
    }
    p_window->draw(*m_mainShape);
}
