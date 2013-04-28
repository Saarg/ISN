#ifndef MISSILE_H
#define MISSILE_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>

class missile
{
    public:
        missile();
        missile(sf::Vector2f size, sf::Color color, sf::Vector2f position, sf::Vector2f speed);
        virtual ~missile();

        void setPosition(sf::Vector2f position);
        void setVector(sf::Vector2f vector);
        //setShapeOptions
        void setColor(sf::Color color);
        void setAngle(float angle);

        sf::Vector2f getPosition();
        sf::Vector2f getVector();
        //getShapeOptions
        sf::Color getColor();
        float getAngle();

        //mainFonctions
        void Move();
        void Draw(sf::RenderWindow* p_window);

    protected:
        float angleV(sf::Vector2f v1, sf::Vector2f v2);
    private:
        sf::Vector2f m_speed;
        float m_angle;
        sf::Clock m_clock;

        sf::ConvexShape* m_mainShape;
};

#endif // MISSILE_H
