#ifndef PLAYER_H
#define PLAYER_H

#include "../vaisseau.h"

class player: public vaisseau
{
    public:
        player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab);
        virtual ~player();

        virtual void Move(int x, int y);

        void shooting(int s);

        virtual void Shoot();
        virtual void Move();
        virtual void onHit(float degat);


        void acceleration(int dir);//Droite Gauche Haut Bas None


    protected:
    private:
        int m_shooting;


};

#endif // PLAYER_H
