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
    player* p =  (player*) (entity_tab[0]);


    float spawnBonus(0);

    Spawn basicSpawn(200, &entity_tab, &missile_tab);

    while (p_window->isOpen())
    {
        basicSpawn.create();

        sf::Event event;
        while (p_window->pollEvent(event))

        {
            //int RandomBonus;
            //RandomBonus = rand()%1001;
            if (event.type == sf::Event::Closed)
                p_window->close();
            else if(((event.type == sf::Event::MouseButtonPressed) or (event.type == sf::Event::MouseButtonReleased)) and (event.mouseButton.button == sf::Mouse::Left))
                p->shooting(sf::Mouse::isButtonPressed(sf::Mouse::Left));
            else if (event.type == sf::Event::LostFocus and !pause(p_window, false))
            {
                if(!pause(p_window, false))
                    p_window->close();
                else
                {
                    //TODO reset des timers entity, missiles, bonus
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if(!pause(p_window, true))
                    p_window->close();
                else
                {
                    //TODO reset des timers entity, missiles, bonus
                }
            }
        }

        //if(sf::Mouse::getPosition(*p_window).x-10 > 0 and sf::Mouse::getPosition(*p_window).y-10 > 0 and sf::Mouse::getPosition(*p_window).y < (float) p_window->getSize().y and sf::Mouse::getPosition(*p_window).x < (float) p_window->getSize().x)
        //    p->setPosition(sf::Mouse::getPosition(*p_window).x-10, sf::Mouse::getPosition(*p_window).y-10);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            p->acceleration(2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            p->acceleration(3);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            p->acceleration(0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            p->acceleration(1);

        p_window->clear();

        backgroung.Draw(p_window);

        for(std::vector<missile*>::size_type i = 0 ; i < missile_tab.size() ; i++)//parcour de tous les missiles
        {
            missile_tab[i]->Draw(p_window);//on le dessine
            if(missile_tab[i]->getPosition().x < 0 or missile_tab[i]->getPosition().y < 0 or missile_tab[i]->getPosition().y > p_window->getSize().y or missile_tab[i]->getPosition().x > p_window->getSize().x)//si or de la fenetre
                missile_tab.erase(missile_tab.begin()+i);//on le suprime
            else//sinon on regarde les colisions
            {
                for(std::vector<vaisseau*>::size_type j = 0 ; j < entity_tab.size() ; j++)
                {
                    sf::FloatRect entityBound = entity_tab[j]->getGlobalBound();//recupération des donnée du vaisseau

                    if(entityBound.left < -50 or entityBound.top < -50 or entityBound.top > p_window->getSize().y+50 or entityBound.left > p_window->getSize().x+50)//on en profite pour regarder si il est bien dans la fenetre
                    {
                        entity_tab.erase(entity_tab.begin()+j);
                    }
                    else if(
                        missile_tab[i]->getPosition().x > entityBound.left and missile_tab[i]->getPosition().x < entityBound.left+entityBound.width and
                        missile_tab[i]->getPosition().y > entityBound.top and missile_tab[i]->getPosition().y < entityBound.top+entityBound.height)//le missile touche-il l'entité?
                    {
                        missile_tab.erase(missile_tab.begin()+i);//supression du missile
                        entity_tab[j]->onHit(1.f);//on inflige 1 de degat a l'entité


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

            if(bonusBound.left+bonusBound.width<0 or bonusBound.left>(float) p_window->getSize().x or bonusBound.top+bonusBound.height<0 or bonusBound.top > (float) p_window->getSize().y)
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

bool pause(sf::RenderWindow* p_window, bool f)
{
    sf::Clock c;

    sf::Font font;
    if (!font.loadFromFile("foughtknight.ttf"))                        //police d'écriture
        return false;

    bool focus = f;

    sf::Text textpause("pause", font, 50);
    sf::Text textquit("quitter: press Echap", font, 50);
    sf::Text textgo("reprendre: press Return", font, 50);

    textpause.setPosition(p_window->getSize().x/2-(textpause.getGlobalBounds().width)/2, 100);
    textquit.setPosition(p_window->getSize().x/2-(textquit.getGlobalBounds().width)/2, 200);
    textgo.setPosition(p_window->getSize().x/2-(textgo.getGlobalBounds().width)/2, 250);
    while (p_window->isOpen())
    {
        sf::Event event;
        while (p_window->pollEvent(event))
        {
            if (event.type == sf::Event::GainedFocus)
                focus = true;
            else if(event.type == sf::Event::LostFocus)
                focus = false;
            else if (focus and ((event.type == sf::Event::Closed) or (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) and c.getElapsedTime() > sf::seconds(0.5f))
                return false;
            else if (focus and (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)))
                return true;

        }

        p_window->draw(textpause);
        p_window->draw(textquit);
        p_window->draw(textgo);
        p_window->display();
    }
    return false;
}
