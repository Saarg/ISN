#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <iostream>
class Bonus
{
    public:
        Bonus(sf::Vector2f position, sf::Color couleur1,sf::Color couleur2, float value);
        virtual ~Bonus();
        void Draw(sf::RenderWindow* p_window);
        sf::Vector2f getPosition();
        sf::FloatRect getGlobalBound();
        void Move();
        float bonusVal();
        sf::Color getFillColor();
        sf::Color getOutlineColor();
        sf::Vector2f getSize();

    protected:
        sf::RectangleShape* m_mainShape;
        sf::Vector2f m_speed;
        float m_bonusValue;
        sf::Clock m_clock;




};

#endif // BONUS_H_INCLUDED
