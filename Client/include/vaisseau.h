#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <vector>
#include "missile.h"

class vaisseau
{
    public:
        vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);
        vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, std::vector<sf::Vector2f> shots, sf::Vector2f speed, sf::Color color, int life);
        virtual ~vaisseau();

        //Position
        void setPosition(int x, int y);

        virtual void Move(int x, int y);

        sf::Vector2f getPosition();
        sf::FloatRect getGlobalBound();
        float getRotation();
        void setRotation(float angle);


        //setShapeOptions
        void setColor(sf::Color color);

        //getShapeOptions
        sf::Color getColor();

        bool isAlive();
        void clockSpeed(float clockchange);

        //mainFonctions
        virtual void Shoot();
        virtual void Move();
        virtual void onHit(float degat);
        void changeScore(sf::Color c1, sf::Color c2, sf::Vector2f size);//R=1 G=2 B=3

        void Draw(sf::RenderWindow* p_window);

    protected:
        sf::Shape* m_mainShape;

        std::vector<missile*>* m_msList;
        std::vector<vaisseau*>* m_entity_tab;
        std::vector<sf::Vector2f> m_shots;

        sf::Vector2f m_speed;
        float m_life;
        int m_scoreR, m_scoreG, m_scoreB;

        sf::Time m_shootFreq;
        sf::Clock m_clock, m_clock2;
        sf::Texture m_texture;
    private:
};

#endif // VAISSEAU_H
