#include "../../include/player/vaisseau.h"

vaisseau::vaisseau()
{
    m_mainShape = new sf::CircleShape(10.f);
    m_mainShape->setFillColor(sf::Color::Red);
    m_mainShape->setPosition(sf::Vector2f(200, 0));

    m_shootFreq = sf::seconds(0.1f);
    m_shootTime = 0;
    m_nbr_msl = 0;

    life = 100;
}

vaisseau::~vaisseau()
{
    //delete m_mainShape;
}

void vaisseau::setPosition(sf::Vector2f position)
{
    m_mainShape->setPosition(position);
}
void vaisseau::setPosition(int x, int y)
{
    m_mainShape->setPosition(x, y);
}
void vaisseau::setPosition(float x, float y)
{
    m_mainShape->setPosition(x, y);
}

//setShapeOptions
void vaisseau::setColor(sf::Color color)
{
    m_mainShape->setFillColor(color);
}

void vaisseau::setAngle(float angle)
{
    m_mainShape->setRotation(angle);
}

sf::Vector2f vaisseau::getPosition()
{
    return m_mainShape->getPosition();
}

//getShapeOptions

sf::Color vaisseau::getColor()
{
    return m_mainShape->getFillColor();
}

float vaisseau::getAngle()
{
    return m_angle;
}

//mainFonctions
void vaisseau::Shoot()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and !(getPosition().x < 5 or getPosition().x > 795 or getPosition().y < 600 or getPosition().y > 900)
            and m_shootTime > 20)//frequence de tir = 20/60 = 0.3s
    {
        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y+10), sf::Vector2f(5,-10)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y+10), sf::Vector2f(0,-10)));
        m_nbr_msl++;

        m_msList.push_back(missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+10, getPosition().y+10), sf::Vector2f(-5,-10)));
        m_nbr_msl++;

        m_shootTime = 0;
    }
    else{m_shootTime++;}
}

void vaisseau::Move()
{

}

void vaisseau::onHit(float degat, std::vector<vaisseau*>* entity_tab, int id)
{
    life -= degat;
}

void vaisseau::Draw(sf::RenderWindow* p_window, std::vector<vaisseau*>* entity_tab)
{
    Move();
    Shoot();

    for(std::vector<missile>::size_type i = 0 ; i < m_msList.size() ; i++)//Parcour de la liste des missiles TODO passer cette liste en pointeurs de missiles (héritage)
    {
        for(std::vector<vaisseau*>::size_type j = 0 ; j < entity_tab->size() ; j++)//Parcour de la liste des entitée via pointeur
        {
            sf::Vector2f entitiesPos = entity_tab->at(j)->getPosition();
            if(entitiesPos == getPosition() or m_msList[i].getPosition().x < entitiesPos.x or m_msList[i].getPosition().x > entitiesPos.x+20 or m_msList[i].getPosition().y < entitiesPos.y or m_msList[i].getPosition().y > entitiesPos.y+20){
            }//si missiles n'est pas sur une entitée on fait rien
            else{
                m_msList.erase(m_msList.begin()+i);//Misile explose
                entity_tab->at(j)->onHit(0.f, entity_tab, j);//entitée est touchée
            }
        }

        m_msList[i].Move();
        m_msList[i].Draw(p_window);

        if(m_msList[i].getPosition().x < 0 or m_msList[i].getPosition().y < 0 or m_msList[i].getPosition().y > 900 or m_msList[i].getPosition().x > 800)
            m_msList.erase(m_msList.begin()+i);//On degage les missiles hors fenetre!
    }
    p_window->draw(*m_mainShape);//On se dessine soi même!
}
