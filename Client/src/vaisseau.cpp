#include "../include/vaisseau.h"

vaisseau::vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab)
{
    m_msList = p_mslist;
    m_entity_tab = p_entity_tab;
    m_mainShape = new sf::RectangleShape(sf::Vector2f(30, 30));

    if (!m_texture.loadFromFile("ressources/carac/vaisseau.png"))
        std::cout << "ressources/carac/vaisseau.png introuvable" << std::endl;

    m_mainShape->setTexture(&m_texture);
    m_mainShape->setOrigin(sf::Vector2f(m_mainShape->getGlobalBounds().width/2, m_mainShape->getGlobalBounds().height/2));

    m_mainShape->setFillColor(sf::Color::Red);
    m_mainShape->setPosition(sf::Vector2f(200, 0));

    m_clock.restart();
    m_shootFreq = sf::seconds(0.5f);

    m_speed = sf::Vector2f(0, 0);
    m_life = 100;
}

vaisseau::vaisseau(std::vector<missile*>* p_mslist, std::vector<vaisseau*>* p_entity_tab, std::vector<sf::Vector2f> shots, sf::Vector2f speed, sf::Color color, int life)
{
    m_msList = p_mslist;
    m_entity_tab = p_entity_tab;
    m_shots = shots;
    m_mainShape = new sf::RectangleShape(sf::Vector2f(30, 30));

    if (!m_texture.loadFromFile("ressources/carac/vaisseau.png"))
        std::cout << "ressources/carac/vaisseau.png introuvable" << std::endl;

    m_mainShape->setTexture(&m_texture);
    m_mainShape->setOrigin(sf::Vector2f(m_mainShape->getGlobalBounds().width/2, m_mainShape->getGlobalBounds().height/2));

    m_mainShape->setFillColor(color);
    m_mainShape->setPosition(sf::Vector2f(200, 0));

    m_clock.restart();
    m_shootFreq = sf::seconds(0.5f);

    m_speed = speed;
    m_life = life;
}

vaisseau::~vaisseau()
{

}

void vaisseau::setPosition(int X, int Y)
{
    m_mainShape->setPosition(X, Y);
}

void vaisseau::Move(int x, int y)
{
    m_mainShape->move(x, y);
}

sf::Vector2f vaisseau::getPosition()
{
    return m_mainShape->getPosition();
}

sf::Vector2f vaisseau::getSpeed()
{
    return m_speed;
}

sf::FloatRect vaisseau::getGlobalBound()
{
    return m_mainShape->getGlobalBounds();
}

float vaisseau::getRotation()
{
    return m_mainShape->getRotation();
}

void vaisseau::setRotation(float angle)
{
    m_mainShape->rotate(angle);
}

void vaisseau::setColor(sf::Color color)
{
    m_mainShape->setFillColor(color);
}

sf::Color vaisseau::getColor()
{
    return m_mainShape->getFillColor();

}

bool vaisseau::isAlive()
{
    if(m_life <= 0)
        return false;
    else
        return true;
}

void vaisseau::Shoot()
{
    if(m_clock.getElapsedTime() > m_shootFreq)
    {
        for(std::vector<sf::Vector2f>::size_type i = 0 ; i < m_shots.size() ; i++)
        {
            m_msList->push_back(new missile(sf::Vector2f(3, 10), sf::Color::Green, sf::Vector2f(getGlobalBound().left+getGlobalBound().width/2, getGlobalBound().top+getGlobalBound().height+5), m_shots[i]));
        }
        m_clock.restart();
    }
}

void vaisseau::Move()
{
    sf::Time time = m_clock2.restart();
    m_mainShape->move(m_speed*(time.asSeconds()*60));
}

void vaisseau::onHit(float degat)
{
    m_life -= degat;
}

void vaisseau::changeScore(sf::Color c1, sf::Color c2, sf::Vector2f size)
{
    m_scoreR = m_scoreR + abs(c1.r-c2.r)*(size.x/5);
    m_scoreG = m_scoreG + abs(c1.g-c2.g)*(size.x/5);
    m_scoreB = m_scoreB + abs(c1.b-c2.b)*(size.x/5);
}

void vaisseau::Draw(sf::RenderWindow* p_window)
{
    Move();
    Shoot();

    float x=getGlobalBound().width/3, y=(int)(sqrt(m_speed.y*m_speed.y))*10;
    float A=(-4*y)/(x*x), B=-(-4*y)/x;

    sf::VertexArray propul = sf::VertexArray(sf::Points, x*y+1);//le +1 au tableau previend tout debordement du au float
    for(int i = 0 ; i < y ; i++)
    {
        for(int j = 0 ; j < x ; j++)
        {
            float YMAX=A*(j*j)+B*j;

            int alpha = 255-(i/YMAX)*255;
            if(alpha<0)
                alpha = 0;

            int R = 255;
            int G = 100;
            int B = 70;



            if(m_speed.y > 0)
                propul[i*x+j].position = getPosition()+sf::Vector2f(j-(x/2), -getGlobalBound().width/2-i);
            else
                propul[i*x+j].position = getPosition()+sf::Vector2f(j-(x/2), getGlobalBound().width/2+i);
            propul[i*x+j].color = sf::Color(R, G, B, alpha);
        }
    }

    p_window->draw(propul);
    p_window->draw(*m_mainShape);

    if(m_life <= 0)
    {
        for(std::vector<vaisseau*>::size_type j = 0 ; j < m_entity_tab->size() ; j++)
        {
            if(m_entity_tab->at(j) == this)
                m_entity_tab->erase(m_entity_tab->begin()+j);
        }
    }
}
