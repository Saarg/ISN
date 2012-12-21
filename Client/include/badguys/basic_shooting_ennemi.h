#ifndef BASIC_SHOOTING_ENNEMI_H_INCLUDED
#define BASIC_SHOOTING_ENNEMI_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../badguys/basic_ennemi.h"

class basic_shooting_ennemi: public basic_ennemi
{
    public:
        basic_shooting_ennemi();
        virtual void Shoot();



};


#endif // BASIC_SHOOTING_ENNEMI_H_INCLUDED
