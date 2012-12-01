#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../missile.h"

class vaisseau
{
    public:
        vaisseau();
        virtual ~vaisseau();

        void setPosition(sf::Vector2f position);
        void setPosition(int x, int y);
        void setPosition(float x, float y);
        //setShapeOptions
        void setColor(sf::Color color);
        void setAngle(float angle);

        sf::Vector2f getPosition();
        //getShapeOptions
        sf::Color getColor();
        float getAngle();

        //mainFonctions
        virtual void Shoot(sf::RenderWindow* p_window);
        virtual void Move();
        virtual void onHit(float degat);
        void Draw(sf::RenderWindow* p_window);

    protected:
        sf::Shape* m_mainShape;
        float m_angle;
        sf::Time m_shootFreq;
        std::vector<missile> m_msList;
        int m_nbr_msl;
        float life;

        sf::Clock m_clock;
    private:

};

#endif // VAISSEAU_H
