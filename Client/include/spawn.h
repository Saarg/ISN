#ifndef SPAWN_H_INCLUDED
#define SPAWN_H_INCLUDED
#include "vaisseau.h"
#include "badguys/basic_shooting_ennemi.h"
#include "badguys/basic_ennemi.h"
#include "modules/modules.h"




class Spawn
{
    public:
        Spawn(int seed, std::vector<vaisseau*>* p_entity_tab, std::vector<missile*>* p_mslist);
        void create();


    private:
        sf::Clock m_clock;

        int m_Random;
        std::vector<vaisseau*>* m_entity_tab;
        std::vector<missile*>* m_msList;




};


#endif // SPAWN_H_INCLUDED
