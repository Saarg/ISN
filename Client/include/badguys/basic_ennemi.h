#ifndef BASIC_ENNEMI_H
#define BASIC_ENNEMI_H

#include <SFML/Graphics.hpp>
#include "../vaisseau.h"

class basic_ennemi: public vaisseau
{
    public:
        basic_ennemi(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);

        virtual void Shoot();
    protected:
    private:

};

#endif // BASIC_ENNEMI_H
