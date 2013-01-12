#include "../../include/badguys/basic_ennemi.h"

basic_ennemi::basic_ennemi(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab):vaisseau(p_mslist, p_entity_tab)
{
    m_life = 1;
}

void basic_ennemi::Shoot()
{

}

void basic_ennemi::Move()
{
    m_mainShape->move(sf::Vector2f(0, 3));
}
