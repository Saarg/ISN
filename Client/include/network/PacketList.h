#ifndef PACKETLIST_H
#define PACKETLIST_H

#include <SFML/Network.hpp>
#include <vector>

class PacketList
{
    public:
        PacketList(sf::TcpSocket* s);
        virtual ~PacketList();

        void Run();
        std::vector<sf::Packet> getPacketTab();
    protected:
    private:
        bool running, clear;

        sf::TcpSocket* socket;
        std::vector<sf::Packet> packet_tab;
};

#endif // PACKETLIST_H
