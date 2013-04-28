#include "solo.h"

int solo(sf::RenderWindow* p_window)
{
    p_window->setSize(sf::Vector2u(800, 900));
    p_window->setFramerateLimit(60);
    p_window->setMouseCursorVisible(false);

    mapping backgroung;

    sf::Font font;
    std::vector<vaisseau*> entity_tab;
    std::vector<missile*> missile_tab;
    std::vector<Bonus*> bonus_tab;


    entity_tab.push_back(new player(&missile_tab, &entity_tab));



    float spawnBonus(0);
    bool continuer = true;
    bool pause = false;

     Spawn basicSpawn(200, &entity_tab, &missile_tab);

    while (p_window->isOpen() && continuer)
    {
        basicSpawn.create();

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

        backgroung.Draw(p_window);

        for(std::vector<missile*>::size_type i = 0 ; i < missile_tab.size() ; i++)
        {
            if(missile_tab[i]->getPosition().x < 0 or missile_tab[i]->getPosition().y < 0 or missile_tab[i]->getPosition().y > 900 or missile_tab[i]->getPosition().x > 800)
                missile_tab.erase(missile_tab.begin()+i);
            else
            {
                missile_tab[i]->Draw(p_window);
                for(std::vector<vaisseau*>::size_type j = 0 ; j < entity_tab.size() ; j++)
                {
                    sf::FloatRect entityBound = entity_tab[j]->getGlobalBound();

                    if(entityBound.left < 0 or entityBound.top < 0 or entityBound.top > 900 or entityBound.left > 800)
                    {
                        entity_tab.erase(entity_tab.begin()+j);
                    }
                    else if(
                        missile_tab[i]->getPosition().x > entityBound.left and missile_tab[i]->getPosition().x < entityBound.left+entityBound.width and
                        missile_tab[i]->getPosition().y > entityBound.top and missile_tab[i]->getPosition().y < entityBound.top+entityBound.height)
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

        sf::FloatRect playerBound = entity_tab[0]->getGlobalBound();

        for(std::vector<Bonus*>::size_type a = 0 ; a < bonus_tab.size() ; a++)
        {
            sf::FloatRect bonusBound = bonus_tab[a]->getGlobalBound();

            if(bonusBound.left<0 or bonusBound.left>793 or bonusBound.top<0 or bonusBound.top > 885)
            {
                bonus_tab.erase(bonus_tab.begin()+a);
            }
            else if(!(bonusBound.left<playerBound.left or bonusBound.left>playerBound.left+playerBound.width or bonusBound.top<playerBound.top or bonusBound.top>playerBound.top+playerBound.height)
                or !(bonusBound.left+bonusBound.width<playerBound.left or bonusBound.left+bonusBound.width>playerBound.left+playerBound.width or bonusBound.top<playerBound.top or bonusBound.top>playerBound.top+playerBound.height)
                or !(bonusBound.left<playerBound.left or bonusBound.left>playerBound.left+playerBound.width or bonusBound.top+bonusBound.height<playerBound.top or bonusBound.top+bonusBound.height>playerBound.top+playerBound.height)
                or !(bonusBound.left+bonusBound.width<playerBound.left or bonusBound.left+bonusBound.width>playerBound.left+playerBound.width or bonusBound.top+bonusBound.height<playerBound.top or bonusBound.top+bonusBound.height>playerBound.top+playerBound.height))
            {
                entity_tab[0]->changeScore(bonus_tab[a]->getFillColor(), bonus_tab[a]->getOutlineColor(), bonus_tab[a]->getSize());
                bonus_tab.erase(bonus_tab.begin()+a);

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
