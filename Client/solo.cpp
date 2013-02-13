#include "solo.h"

int solo()
{
    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML works!");
    window.setFramerateLimit(60);
    std::vector<vaisseau*> entity_tab;
    std::vector<missile*> missile_tab;

    entity_tab.push_back(new player(&missile_tab, &entity_tab));
    entity_tab.push_back(new basic_shooting_ennemi(&missile_tab, &entity_tab));

    srand(404);
    int Random;

    while (window.isOpen())
    {
        /* gestion aléatoire des gros pas bô */
        Random = rand()%1001;//nombre entre 0 et 1000
        if(Random < 10){//1% de chance de spawn un pas joli
            entity_tab.push_back(new basic_ennemi(&missile_tab, &entity_tab));
            entity_tab[entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
        }
        else if(Random < 50 and Random > 48){//0.2% de chance d'un escadron de pas bô
            entity_tab.push_back(new basic_shooting_ennemi(&missile_tab, &entity_tab));
            entity_tab[entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
        }
        else if(Random < 55 and Random > 50){//0.2% de chance d'un escadron de pas bô
            entity_tab.push_back(new basic_ennemi(&missile_tab, &entity_tab));
            entity_tab[entity_tab.size()-1]->setPosition(rand()%781, 0);//On oubli pas la position random
            entity_tab.push_back(new modules(&missile_tab, &entity_tab, entity_tab[entity_tab.size()-1], sf::Vector2f(0, 20), sf::Vector2f(3, -10)));
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        if(sf::Mouse::getPosition(window).x-10 > 0 and sf::Mouse::getPosition(window).y-10 > 0 and sf::Mouse::getPosition(window).y < 900 and sf::Mouse::getPosition(window).x < 800)
            entity_tab[0]->setPosition(sf::Mouse::getPosition(window).x-10, sf::Mouse::getPosition(window).y-10);

        window.clear();

        for(std::vector<missile*>::size_type i = 0 ; i < missile_tab.size() ; i++)
        {
            if(missile_tab[i]->getPosition().x < 0 or missile_tab[i]->getPosition().y < 0 or missile_tab[i]->getPosition().y > 900 or missile_tab[i]->getPosition().x > 800)
                missile_tab.erase(missile_tab.begin()+i);
            else
            {
                missile_tab[i]->Draw(&window);
                for(std::vector<vaisseau*>::size_type j = 0 ; j < entity_tab.size() ; j++)
                {
                    sf::Vector2f entityPos = entity_tab[j]->getPosition();

                    if(entityPos.x < 0 or entityPos.y < 0 or entityPos.y > 900 or entityPos.x > 800)
                    {
                        entity_tab.erase(entity_tab.begin()+j);
                    }
                    else if(
                        missile_tab[i]->getPosition().x > entityPos.x and missile_tab[i]->getPosition().x < entityPos.x+20 and
                        missile_tab[i]->getPosition().y > entityPos.y and missile_tab[i]->getPosition().y < entityPos.y+20)
                    {
                        missile_tab.erase(missile_tab.begin()+i);
                        entity_tab[j]->onHit(1.f);
                    }

                }
            }
        }
        for(std::vector<vaisseau*>::size_type i = 0 ; i < entity_tab.size() ; i++)
        {
            entity_tab.at(i)->Draw(&window);
        }
        window.display();
    }

    return 0;
}
