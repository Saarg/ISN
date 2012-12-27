#ifndef BASIC_SHOOTING_ENNEMI_H_INCLUDED
#define BASIC_SHOOTING_ENNEMI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../badguys/basic_ennemi.h"

class basic_shooting_ennemi: public basic_ennemi
{
    public:
        basic_shooting_ennemi(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);
        virtual void Shoot();
        virtual void Move();



};


#endif // BASIC_SHOOTING_ENNEMI_H_INCLUDED
