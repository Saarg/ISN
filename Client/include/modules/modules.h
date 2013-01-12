#ifndef MODULES_H
#define MODULES_H

#include "../vaisseau.h"

class modules: public vaisseau
{
    public:
        modules(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, vaisseau* p_master);
        modules(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, vaisseau* p_master, sf::Vector2f posRel, sf::Vector2f shootDir);
        virtual ~modules();

        void setPositionRel(sf::Vector2f posRel);

        virtual void Shoot();
        virtual void Move();
        virtual void onHit(float degat);
    protected:
        vaisseau* m_master;

        sf::Vector2f m_posRel, m_shootDir;
    private:
};

#endif // MODULES_H
