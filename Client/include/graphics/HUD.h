#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <sstream>

class HUD
{
    public:
        HUD();
        virtual ~HUD();

        void changeScore(sf::Color c1, sf::Color c2, float bonusval);//R=1 G=2 B=3
        void Draw(sf::RenderWindow* p_window);
    protected:
    private:
        sf::Font m_font;
        sf::Text m_scoreR, m_scoreG, m_scoreB;
        int m_R, m_G, m_B;
};

#endif // HUD_H
