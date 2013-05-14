#include "../include/spawn.h"

Spawn::Spawn(int seed, std::vector<vaisseau*>* p_entity_tab, std::vector<missile*>* p_mslist)
{
    m_msList = p_mslist;
    m_entity_tab = p_entity_tab;
}
void Spawn::create()
{
    if(m_clock.getElapsedTime() > sf::seconds(1/6))
    {
        m_Random = rand()%1001;
        if(m_Random < 10){
            std::vector<sf::Vector2f> shots;
            m_entity_tab->push_back(new vaisseau(m_msList, m_entity_tab, shots, sf::Vector2f(0, 3), sf::Color::Red, 1));
            m_entity_tab->at(m_entity_tab->size()-1)->setPosition(rand()%800, -10);//SpawnX=random, le Y = -50 permet une arrivé plus "fluide"
        }
        else if(m_Random < 50 and m_Random > 48){
            std::vector<sf::Vector2f> shots;
            shots.push_back(sf::Vector2f(0, 10));
            m_entity_tab->push_back(new vaisseau(m_msList, m_entity_tab, shots, sf::Vector2f(0, 3), sf::Color::Yellow, 1));
            m_entity_tab->at(m_entity_tab->size()-1)->setPosition(rand()%800, -10);
        }
        else if(m_Random < 55 and m_Random > 50){
            std::vector<sf::Vector2f> shots;
            shots.push_back(sf::Vector2f(3, 10));
            shots.push_back(sf::Vector2f(-3, 10));
            m_entity_tab->push_back(new vaisseau(m_msList, m_entity_tab, shots, sf::Vector2f(0, 3), sf::Color::Green, 1));
            m_entity_tab->at(m_entity_tab->size()-1)->setPosition(rand()%800, -10);
        }
    }
}
