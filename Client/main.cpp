#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <time.h>

#include "include/player/vaisseau.h"
#include "include/badguys/basic_shooting_ennemi.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
    window.setFramerateLimit(60);
    int player = 0;//Le joueur est dans la ligne 0
    std::vector<vaisseau*> entity_tab;

    entity_tab.push_back(new vaisseau());
    entity_tab.push_back(new basic_shooting_ennemi());

    srand(547);
    int Random;

    while (window.isOpen())
    {
        /* gestion aléatoire des gros pas bô */
        Random = rand()%1001;//nombre entre 0 et 1000
        if(Random < 10){//1% de chance de spawn un pas joli
            entity_tab.push_back(new basic_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random

        }
        if(Random < 50 and Random > 48){//0.2% de chance d'un escadron de pas bô
            entity_tab.push_back(new basic_shooting_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random

        }
        entity_tab[entity_tab.size()-1]->Shoot();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        entity_tab[player]->setPosition(sf::Mouse::getPosition(window).x-10, sf::Mouse::getPosition(window).y-10);

        window.clear();
        for(std::vector<vaisseau*>::size_type i = 0 ; i < entity_tab.size() ; i++){//c'est parti on affiche tout le monde!!!
            entity_tab[i]->Draw(&window, &entity_tab);

            if(entity_tab[i]->getPosition().x < 0 or entity_tab[i]->getPosition().x > 800 or entity_tab[i]->getPosition().y > 900 or entity_tab[i]->getPosition().y < 0)
                entity_tab.erase(entity_tab.begin()+i);

        }
        window.display();
    }

    return 0;
}

