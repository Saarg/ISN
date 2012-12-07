#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <time.h>

#include "include/player/vaisseau.h"
#include "include/badguys/basic_ennemi.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
    window.setFramerateLimit(60);
    int player = 0;//Le joueur est dans la ligne 0

    /* toutes les variables pour afficher les fps */
    sf::Time frameTime;
    sf::Clock clock;
    int framerate;
    sf::Font font;
    if (!font.loadFromFile("Little Snorlax.ttf"))
    {
        std::cout << "cannotloadfont" << std::endl;
    }
    sf::Text FPSText;
    FPSText.setFont(font);
    FPSText.setPosition(750, 10);
    FPSText.setCharacterSize(20);

    /* Liste des entitées, a travers des pointers */
    std::vector<vaisseau*> entity_tab;

    entity_tab.push_back(new vaisseau());
    entity_tab.push_back(new basic_ennemi());

    int Random;

    while (window.isOpen())
    {
        /* On relève et affiche les FPS */
        frameTime = clock.restart();
        framerate = (int) (1 / (frameTime.asSeconds()));
        std::ostringstream oss;
        oss << framerate;
        FPSText.setString(oss.str());

        /* gestion aléatoire des gros pas bô */
        Random = rand()%1001;//nombre entre 0 et 1000
        if(Random < 10){//1% de chance de spawn un pas joli
            entity_tab.push_back(new basic_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(rand()%801, 0);//On oubli pas la position random
        }
        if(Random < 50 and Random > 48){//0.2% de chance d'un escadron de pas bô
            Random = rand()%801;//On oubli pas la position random
            entity_tab.push_back(new basic_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(Random, 0);
            entity_tab.push_back(new basic_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(Random-15, -20);
            entity_tab.push_back(new basic_ennemi());
            entity_tab[entity_tab.size()-1]->setPosition(Random+15, -20);
        }

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
        }
        window.draw(FPSText);
        window.display();
    }

    return 0;
}

