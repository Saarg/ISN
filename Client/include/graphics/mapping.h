#ifndef MAPPING_H
#define MAPPING_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <iostream>

class mapping
{
    public:
        mapping();
        virtual ~mapping();

        void Draw(sf::RenderWindow* p_window);
    protected:
    private:
        sf::Clock m_clock;

        sf::Vector2f m_pos;
        std::vector<sf::Texture>  m_texture_tab;
        sf::Sprite m_mapping[9][11];

};

#endif // MAPPING_H
