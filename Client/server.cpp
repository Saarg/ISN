#include "server.h"

server::server()
{
    m_serveur_lance = false;
}

server::server(int seed)
{
    m_seed = seed;
    m_serveur_lance = false;
}

server::~server()
{
    //dtor
}

void server::Run()
{
    m_serveur_lance = true;
    std::cout << "écoute du port 25565" << std::endl;
    Listen();
    std::cout << "lancement de la game" << std::endl;
    srand(404);
    int Random;
    while(m_serveur_lance)
    {
        Random = rand()%1001;//nombre entre 0 et 1000
        if(Random < 10){//1% de chance de spawn un pas joli
            m_entity_tab.push_back(new basic_ennemi(&m_missile_tab, &m_entity_tab));
            m_entity_tab[m_entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
        }
        else if(Random < 50 and Random > 48){//0.2% de chance d'un escadron de pas bô
            m_entity_tab.push_back(new basic_shooting_ennemi(&m_missile_tab, &m_entity_tab));
            m_entity_tab[m_entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
        }
        else if(Random < 55 and Random > 50){//0.2% de chance d'un escadron de pas bô
            m_entity_tab.push_back(new basic_ennemi(&m_missile_tab, &m_entity_tab));
            m_entity_tab[m_entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
            m_entity_tab.push_back(new modules(&m_missile_tab, &m_entity_tab, m_entity_tab[m_entity_tab.size()-1], sf::Vector2f(0, 20), sf::Vector2f(3, -10)));
        }
        Read();
    }
}

void server::Listen()
{
    int clientco = 0;
    sf::TcpListener listener;
    listener.listen(25565);

    while (clientco < 2)
    {
        std::cout << "attente des clients" << std::endl;
        if (listener.accept(m_client[clientco]) == sf::Socket::Done)
        {
            std::cout << clientco << "client co" << std::endl;
            clientco++;
        }
    }
}

sf::Packet server::Read()
{
    sf::Packet packet;
    m_client[0].receive(packet);
    return packet;
}

void server::SendAll(sf::Packet packet)
{
    m_client[0].send(packet);
    m_client[1].send(packet);
}

bool server::isRunning()
{
    return m_serveur_lance;
}
