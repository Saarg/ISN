#include "solo.h"
#include "include/bonus.h"
#include <SFML/Graphics.hpp>

int solo(sf::RenderWindow* p_window)
{
    p_window->setSize(sf::Vector2u(800, 900));
    p_window->setFramerateLimit(1000);

    sf::Font font;
    std::vector<vaisseau*> entity_tab;
    std::vector<missile*> missile_tab;
    std::vector<Bonus*> bonus_tab;

    entity_tab.push_back(new player(&missile_tab, &entity_tab));
    entity_tab.push_back(new basic_shooting_ennemi(&missile_tab, &entity_tab));

    srand(404);
    int Random;
    float spawnBonus(0);
    //int bonusScore(0);
    //int bonValue;
    bool continuer = true;
    bool pause = false;


    while (p_window->isOpen() && continuer)
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
        while (p_window->pollEvent(event))

        {
            //int RandomBonus;
            //RandomBonus = rand()%1001;
            if (event.type == sf::Event::Closed)
                p_window->close();
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                pause = true;

                while(pause){
                    sf::Text textpause("pause", font, 50);
                    sf::Text textoui("oui", font, 50);
                    sf::Text textnon("non", font, 50);
                    sf::Text pressEchap("press Echap", font, 50);
                    sf::Text pressReturn("press Return", font, 50);

                    textpause.setPosition(400-(textpause.getGlobalBounds().width)/2, 100);
                    textoui.setPosition(350, 100);
                    textnon.setPosition(50, 200);
                    pressEchap.setPosition(350, 300);
                    pressReturn.setPosition(50, 400);

                    p_window->display();

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                         continuer=false;
                         pause=false;
                    }

                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        pause=false;
                }

        }

        if(sf::Mouse::getPosition(*p_window).x-10 > 0 and sf::Mouse::getPosition(*p_window).y-10 > 0 and sf::Mouse::getPosition(*p_window).y < 900 and sf::Mouse::getPosition(*p_window).x < 800)
            entity_tab[0]->setPosition(sf::Mouse::getPosition(*p_window).x-10, sf::Mouse::getPosition(*p_window).y-10);

        p_window->clear();

        for(std::vector<missile*>::size_type i = 0 ; i < missile_tab.size() ; i++)
        {
            if(missile_tab[i]->getPosition().x < 0 or missile_tab[i]->getPosition().y < 0 or missile_tab[i]->getPosition().y > 900 or missile_tab[i]->getPosition().x > 800)
                missile_tab.erase(missile_tab.begin()+i);
            else
            {
                missile_tab[i]->Draw(p_window);
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


                        if(entity_tab[j]->isAlive()==false)
                        {
                           spawnBonus=spawnBonus+0.8;

                        }
                        if(spawnBonus>2 && spawnBonus!= 2.2)
                        {
                             bonus_tab.push_back(new Bonus(entity_tab[j]->getPosition(),sf::Color::Yellow,sf::Color::Green, 5));
                             spawnBonus = spawnBonus-2;

                        }
                        else if(spawnBonus==2)
                        {
                             bonus_tab.push_back(new Bonus(entity_tab[j]->getPosition(),sf::Color::Cyan, sf::Color::Blue, 10));
                             spawnBonus = spawnBonus-2;

                        }


                    }



                }
            }
        }

        sf::Vector2f playerPos = entity_tab[0]->getPosition();

        for(std::vector<Bonus*>::size_type a = 0 ; a < bonus_tab.size() ; a++)
        {
            sf::Vector2f bonusPos = bonus_tab[a]->getPosition();

            if(bonusPos.x<0 or bonusPos.x>793 or bonusPos.y<0 or bonusPos.y > 885)
            {
                bonus_tab.erase(bonus_tab.begin()+a);
            }
            else if(!(bonusPos.x<playerPos.x or bonusPos.x>playerPos.x+20 or bonusPos.y<playerPos.y or bonusPos.y>playerPos.y+20)
                or !(bonusPos.x+10<playerPos.x or bonusPos.x+10>playerPos.x+20 or bonusPos.y<playerPos.y or bonusPos.y>playerPos.y+20)
                or !(bonusPos.x<playerPos.x or bonusPos.x>playerPos.x+20 or bonusPos.y+10<playerPos.y or bonusPos.y+10>playerPos.y+20)
                or !(bonusPos.x+10<playerPos.x or bonusPos.x+10>playerPos.x+20 or bonusPos.y+10<playerPos.y or bonusPos.y+10>playerPos.y+20))
            {
                bonus_tab.erase(bonus_tab.begin()+a);
                entity_tab[0]->changeScore(bonus_tab[0]->getFillColor(), bonus_tab[0]->getOutlineColor(), bonus_tab[0]->getSize());
            }

        }

        for(std::vector<vaisseau*>::size_type i = 0 ; i < entity_tab.size() ; i++)
        {
            entity_tab.at(i)->Draw(p_window);
        }
        for(std::vector<Bonus*>::size_type u = 0 ; u < bonus_tab.size() ; u++)
        {
            bonus_tab.at(u)->Draw(p_window);
        }

        p_window->display();
    }

    return 0;
}
