#include "../../include/badguys/basic_ennemi.h"

void basic_ennemi::Shoot()
{

}

void basic_ennemi::Move()
{
    m_mainShape->move(sf::Vector2f(0, 3));
}

void basic_ennemi::onHit(float degat, std::vector<vaisseau*>* entity_tab, int id)
{
    delete entity_tab->at(id);
    entity_tab->erase(entity_tab->begin()+id);
}
