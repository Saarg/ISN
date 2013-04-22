#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
class Bonus
{
    public:
        Bonus(sf::Vector2f position, sf::Color couleur1,sf::Color couleur2, int value);
        virtual ~Bonus();
        void Draw(sf::RenderWindow* p_window);
        sf::Vector2f getPosition();
        void Move();
        int bonusVal();
        sf::Color getFillColor();
        sf::Color getOutlineColor();
        sf::Vector2f getSize();

    protected:
        sf::RectangleShape* m_mainShape;
        sf::Vector2f m_speed;
        int m_bonusValue;
        sf::Clock m_clock;




};

#endif // BONUS_H_INCLUDED
