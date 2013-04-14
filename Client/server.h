#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <vector>

#include "include/player/player.h"
#include "include/badguys/basic_shooting_ennemi.h"
#include "include/modules/modules.h"

class server
{
    public:
        server();
        server(int seed);
        virtual ~server();

        void Run();
        void Listen();

        sf::Packet Read();
        void SendAll(sf::Packet packet);

        bool isRunning();

    protected:
    private:
        int m_seed;
        bool m_serveur_lance;

        sf::TcpSocket m_client[2];
        std::vector<vaisseau*> m_entity_tab;
        std::vector<missile*> m_missile_tab;

};

#endif // SERVER_H
