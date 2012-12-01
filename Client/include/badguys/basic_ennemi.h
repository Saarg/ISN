#ifndef BASIC_ENNEMI_H
#define BASIC_ENNEMI_H

#include <SFML/Graphics.hpp>
#include "../player/vaisseau.h"

class basic_ennemi: public vaisseau
{
    public:
        virtual void Move();
    protected:
    private:

};

#endif // BASIC_ENNEMI_H
