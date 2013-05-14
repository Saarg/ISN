#include "../../include/graphics/HUD.h"

HUD::HUD()
{
    m_font.loadFromFile("foughtknight.ttf");

    m_scoreR = sf::Text("0", m_font, 30 );
    m_scoreG = sf::Text("0", m_font, 30 );
    m_scoreB = sf::Text("0", m_font, 30 );

    m_R = m_G = m_B = 0;
}

HUD::~HUD()
{
    //dtor
}

void HUD::changeScore(sf::Color c1, sf::Color c2, float bonusval)
{
    m_R = m_R + abs(c1.r-c2.r)*bonusval;
    m_G = m_G + abs(c1.g-c2.g)*bonusval;
    m_B = m_B + abs(c1.b-c2.b)*bonusval;
}

void HUD::Draw(sf::RenderWindow* p_window)
{
    std::stringstream ssR;//create a stringstream
    ssR << m_R;//add number to the stream
    m_scoreR.setString(ssR.str());
    std::stringstream ssG;
    ssG << m_G;
    m_scoreG.setString(ssG.str());
    std::stringstream ssB;
    ssB << m_B;
    m_scoreB.setString(ssB.str());

    m_scoreR.setPosition(sf::Vector2f(10, 10));
    m_scoreG.setPosition(sf::Vector2f(p_window->getSize().x/2-m_scoreG.getGlobalBounds().width/2, 10));
    m_scoreB.setPosition(sf::Vector2f(p_window->getSize().x-m_scoreG.getGlobalBounds().width-10, 10));

    p_window->draw(m_scoreR);
    p_window->draw(m_scoreG);
    p_window->draw(m_scoreB);
}
