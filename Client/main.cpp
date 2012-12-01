#include <SFML/Graphics.hpp>
#include <vector>

#include "include/player/vaisseau.h"
#include "include/badguys/basic_ennemi.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
    window.setFramerateLimit(60);
    int player = 0;
    //basic_ennemi ennemi1;

    std::vector<vaisseau*> entity_tab;

    while (window.isOpen())
    {
        entity_tab.push_back(new vaisseau());
        entity_tab.push_back(new basic_ennemi());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        entity_tab[player]->setPosition(sf::Mouse::getPosition(window).x-10, sf::Mouse::getPosition(window).y-10);
        entity_tab[player]->Shoot(&window);
        entity_tab[1]->Move();

        window.clear();
        entity_tab[player]->Draw(&window);
        entity_tab[1]->Draw(&window);
        window.display();
    }

    return 0;
}

