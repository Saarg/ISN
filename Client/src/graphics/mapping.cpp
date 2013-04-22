#include "../../include/graphics/mapping.h"

mapping::mapping()
{
    m_pos = sf::Vector2f(0, -100);
    for(int i = 0 ; i < 15 ; i++)
    {
        sf::Texture texture;
        std::ostringstream oss;
        oss << "/home/jean/Documents/projetISN/ISN/Client/ressources/mapping/space"<<i<<".png";
        if (!texture.loadFromFile(oss.str()))
            std::cout << oss.str() << " introuvable" << std::endl;
        else
            m_texture_tab.push_back(texture);
    }
    for(int y = 0 ; y < 10 ; y++)
    {
        for(int x = 0 ; x < 8; x++)
        {
            m_mapping[x][y].setTexture(m_texture_tab[rand()%15]);
            m_mapping[x][y].setPosition(m_pos+sf::Vector2f(x*100, y*100));
        }
    }
}

mapping::~mapping()
{
    //dtor
}

void mapping::Draw(sf::RenderWindow* p_window)
{
    sf::Time time = m_clock.restart();
    m_pos = m_pos + sf::Vector2f(0, time.asSeconds()*60);
    if(m_pos.y > 0)
    {
        m_pos = m_pos + sf::Vector2f(0, -100);
        for(int y = 9 ; y > 0 ; y--)
        {
            for(int x = 0 ; x < 8; x++)
            {
                m_mapping[x][y] = m_mapping[x][y-1];
            }
        }

        for(int x = 0 ; x < 8; x++)
            m_mapping[x][0].setTexture(m_texture_tab[rand()%15]);
    }

    for(int y = 0 ; y < 10 ; y++)
        {
            for(int x = 0 ; x < 8; x++)
            {
            m_mapping[x][y].setPosition(m_pos+sf::Vector2f(x*100, y*100));
            p_window->draw(m_mapping[x][y]);
        }
    }
}
