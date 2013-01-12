#include "../../include/modules/modules.h"

modules::modules(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, vaisseau* p_master):vaisseau(p_mslist, p_entity_tab)
{
    m_master = p_master;

    m_mainShape = new sf::CircleShape(4.f);
    m_mainShape->setFillColor(sf::Color::Yellow);
    m_mainShape->setOutlineColor(m_master->getColor());
    m_mainShape->setOutlineThickness(1);

    m_life = 1;
}

modules::modules(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, vaisseau* p_master, sf::Vector2f posRel, sf::Vector2f shootDir):vaisseau(p_mslist, p_entity_tab)
{
    m_master = p_master;

    m_mainShape = new sf::CircleShape(4.f);
    m_mainShape->setFillColor(sf::Color::Yellow);
    m_mainShape->setOutlineColor(m_master->getColor());
    m_mainShape->setOutlineThickness(1);

    m_life = 1;
    m_posRel = posRel;
    m_shootDir = shootDir;
}

modules::~modules()
{
    //dtor
}

void modules::setPositionRel(sf::Vector2f posRel)
{
    m_posRel = posRel;
}

void modules::Shoot()
{
    if(m_clock.getElapsedTime() > m_shootFreq)
    {
        m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y+20), sf::Vector2f(0, 5)));
        m_clock.restart();
    }
}

void modules::Move()
{
    if(!m_master->isAlive())
        m_life = 0;

    m_mainShape->setPosition(sf::Vector2f((m_master->getPosition().x+5)+m_posRel.x, (m_master->getPosition().y+5)+m_posRel.y));
}

void modules::onHit(float degat)
{
    m_life = m_life-degat;
}
