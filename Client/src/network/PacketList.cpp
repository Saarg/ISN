#include "../../include/network/PacketList.h"

PacketList::PacketList(sf::TcpSocket* s)
{
    socket = s;
    running = false;
    clear = false;
}

PacketList::~PacketList()
{
    //dtor
}

void PacketList::Run()
{
    running = true;
    clear = true;
    socket->setBlocking(true);
    while(running)
    {
        if(clear)
        {
            clear = false;
            packet_tab.clear();
        }
        sf::Packet p;
        socket->receive(p);
        packet_tab.push_back(p);
    }
}

std::vector<sf::Packet> PacketList::getPacketTab()
{
    clear = true;
    return packet_tab;
}
