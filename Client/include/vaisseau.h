#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include "missile.h"

class vaisseau
{
    public:
        vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);
        virtual ~vaisseau();

        //Position
        void setPosition(sf::Vector2f position);
        void setPosition(int x, int y);
        void setPosition(float x, float y);

        sf::Vector2f getPosition();

        //setShapeOptions
        void setColor(sf::Color color);

        //getShapeOptions
        sf::Color getColor();

        bool isAlive();

        //mainFonctions
        virtual void Shoot();
        virtual void Move();
        virtual void onHit(float degat);

        void Draw(sf::RenderWindow* p_window);

    protected:
        sf::Shape* m_mainShape;

        std::vector<missile*>* m_msList;
        std::vector<vaisseau*>* m_entity_tab;

        sf::Vector2f m_speed;
        float m_life;

        sf::Time m_shootFreq;
        sf::Clock m_clock;
    private:
};

#endif // VAISSEAU_H
