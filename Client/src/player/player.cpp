#include "../../include/player/player.h"

player::player(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab): vaisseau(p_mslist, p_entity_tab)
{
    m_shootFreq = sf::seconds(0.3f);

    if (!m_texture.loadFromFile("ressources/carac/player.png"))
        std::cout << "ressources/carac/player.png introuvable" << std::endl;

    m_mainShape->setTexture(&m_texture);

    m_mainShape->setFillColor(sf::Color(100,200,200));
    m_mainShape->setPosition(sf::Vector2f(400, 650));
    m_scoreR = 0;
    m_scoreG = 0;
    m_scoreB = 0;

    m_shots.push_back(sf::Vector2f(0, -10));
    m_shots.push_back(sf::Vector2f(-10*sin(3.14/12), -10*cos(3.14/12)));
    m_shots.push_back(sf::Vector2f(-10*sin(-3.14/12), -10*cos(-3.14/12)));
    m_shots.push_back(sf::Vector2f(-10*sin(3.14/6), -10*cos(3.14/6)));
    m_shots.push_back(sf::Vector2f(-10*sin(-3.14/6), -10*cos(-3.14/6)));
    m_shots.push_back(sf::Vector2f(-10*sin(3.14/3), -10*cos(3.14/3)));
    m_shots.push_back(sf::Vector2f(-10*sin(-3.14/3), -10*cos(-3.14/3)));

    m_shooting = 0;
}

player::~player()
{
    //dtor
}

void player::Move(int x, int y)
{
    m_mainShape->move(x, y);
}

void player::shooting(int s)
{
    m_shooting = s;
}

void player::Shoot()
{
    if(m_shooting != 0 and m_clock.getElapsedTime() > m_shootFreq)
    {
        for(std::vector<sf::Vector2f>::size_type i = 0 ; i < m_shots.size() ; i++)
        {
            sf::Vector2f dir;
            float a = 2*3.14*m_mainShape->getRotation()/360;

            if(m_shooting == 1)
                dir = sf::Vector2f(m_shots[i].x*cos(a)-m_shots[i].y*sin(a), m_shots[i].x*sin(a)+m_shots[i].y*cos(a));
            else if(m_shooting == 2)
                dir = sf::Vector2f(m_shots[i].x*cos(a)-2*m_shots[i].y*sin(a), m_shots[i].x*sin(a)+2*m_shots[i].y*cos(a));


            sf::Vector2f canonpos = sf::Vector2f(0*cos(a)-(-getGlobalBound().height)*sin(a),
                                                    0*sin(a)+(-getGlobalBound().height)*cos(a));
            m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getPosition().x+canonpos.x, getPosition().y+canonpos.y), dir));
        }
        m_clock.restart();
    }
}

void player::Move()
{
    if(m_shooting == 1)
    {
        m_speed.x =  m_speed.x - m_speed.x/6;
        m_speed.y =  m_speed.y - m_speed.y/6;
    }
    else if(m_shooting == 2)
    {
        m_speed.x =  m_speed.x - m_speed.x/3;
        m_speed.y =  m_speed.y - m_speed.y/3;
    }
    else
    {
        m_speed.x =  m_speed.x - m_speed.x/12;
        m_speed.y =  m_speed.y - m_speed.y/12;
    }
    sf::Time time = m_clock2.restart();
    m_mainShape->move(m_speed*(time.asSeconds()*60));;
}

void player::onHit(float degat)
{

}

int player::acceleration(int dir)//Droite Gauche Haut Bas None
{
    switch(dir)
    {
        case 0:
            m_speed.x -= 1;
            break;
        case 1:
            m_speed.x += 1;
            break;
        case 2:
            if(m_mainShape->getRotation() != 0)
            {
                m_mainShape->rotate(30);
                return 30;
            }
            else
                m_speed.y -= 1;
            break;
        case 3:
            if(m_mainShape->getRotation() != 180)
            {
                m_mainShape->rotate(30);
                return 30;
            }
            else
                m_speed.y += 1;
            break;
        default:
            break;
    }
    return 0;
}
