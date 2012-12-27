#include "../include/missile.h"

missile::missile()
{
    m_mainShape = new sf::RectangleShape(sf::Vector2f(10, 10));
    m_mainShape->setFillColor(sf::Color::Green);
    m_mainShape->setPosition(sf::Vector2f(10, 10));
    setVector(sf::Vector2f(5, 5));
}

missile::missile(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::Vector2f speed)
{
    m_mainShape = new sf::RectangleShape(size);
    m_mainShape->setFillColor(color);
    m_mainShape->setPosition(position);
    setVector(speed);
}

missile::~missile()
{
    if(m_mainShape->getPosition().x < -30 or m_mainShape->getPosition().x > 830 or m_mainShape->getPosition().y > 930 or m_mainShape->getPosition().y < -30)
        delete m_mainShape;
}

void missile::setPosition(sf::Vector2f position)
{
    m_mainShape->setPosition(position);
}

void missile::setVector(sf::Vector2f vector)
{
    m_speed = vector;
    setAngle(angleV(sf::Vector2f(0, 1), m_speed));
}

//setShapeOptions
void missile::setColor(sf::Color color)
{
    m_mainShape->setFillColor(color);
}

void missile::setAngle(float angle)
{
    m_angle = angle;
    m_mainShape->setRotation(angle);
}

sf::Vector2f missile::getPosition()
{
    return m_mainShape->getPosition();
}

sf::Vector2f missile::getVector()
{
    return m_speed;
}

//getShapeOptions

sf::Color missile::getColor()
{
    return m_mainShape->getFillColor();
}

float missile::getAngle()
{
    return m_angle;
}

//mainFonctions
void missile::Move()
{
    m_mainShape->move(m_speed);
}

void missile::Draw(sf::RenderWindow* p_window)
{
    Move();
    p_window->draw(*m_mainShape);
}

float missile::angleV(sf::Vector2f v1, sf::Vector2f v2)
{
    float produit_scalaire, determinant;

	produit_scalaire	= v1.x*v2.x + v1.y*v2.y;
	determinant		= v1.x*v2.y - v2.x*v1.y;
	//Arevoirl'anglesembleetrangemaiscamarche
	return atan2(determinant, produit_scalaire) * 180 / M_PI;
}
