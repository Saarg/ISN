#ifndef PLAYER_H
#define PLAYER_H

#include "../vaisseau.h"

class player: public vaisseau
{
    public:
        player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);
        virtual ~player();

        void shooting(bool s);

        virtual void Shoot();
        virtual void Move();
        virtual void onHit(float degat);
    protected:
    private:
        bool m_shooting;


};

#endif // PLAYER_H
