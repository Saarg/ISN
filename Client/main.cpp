#include "solo.h"
#include "multiplayer.h"
#include "include/graphics/mapping.h"
#include <SFML/Graphics.hpp>


 int main()
 {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 900), "SFML window");   //creation d'une fenetre de 800/900
    window.setFramerateLimit(60);                                      //limite le programme a 60 fps

    mapping backgroung;

    sf::Font font;
    if (!font.loadFromFile("foughtknight.ttf"))                        //police d'écriture
        return EXIT_FAILURE;

    sf::Text texttitle("SpaceShoot", font, 50);

    sf::Text text[5];
    text[0]=sf::Text("solo", font, 50 );
    text[1]=sf::Text("duel", font, 50 );
    text[2]=sf::Text("multijoueur", font, 50 );
    text[3]=sf::Text("options", font, 50 );
    text[4]=sf::Text("quitter", font, 50 );                            //tableau de caractere

    int a(0);                                                          //a ---> la variable permettant de naviguer dans le menu

    texttitle.setPosition(window.getSize().x/2-(texttitle.getGlobalBounds().width)/2, 100);

    text[0].setPosition(window.getSize().x/2-(text[0].getGlobalBounds().width)/2, 250);
    text[1].setPosition(window.getSize().x/2-(text[1].getGlobalBounds().width)/2, 300);
    text[2].setPosition(window.getSize().x/2-(text[2].getGlobalBounds().width)/2, 350);
    text[3].setPosition(window.getSize().x/2-(text[3].getGlobalBounds().width)/2, 400);
    text[4].setPosition(window.getSize().x/2-(text[4].getGlobalBounds().width)/2, 450); //position des textes

    float x=10, y=50;
    float A=(-4*y)/(x*x), B=-(-4*y)/x;
    sf::VertexArray propul(sf::Points, x*y);
    for(int i = 0 ; i < y ; i++)
    {
        for(int j = 0 ; j < x ; j++)
        {
            float YMAX=A*(j*j)+B*j;

            int alpha = 255-(i/YMAX)*255;
            if(alpha<0)
                alpha = 0;

            int R = 255;
            int G = 100;
            int B = 70;

            propul[i*x+j].position = sf::Vector2f(j, y-i);
            propul[i*x+j].color = sf::Color(R, G, B, alpha);
        }
    }

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        text[a].setColor(sf::Color::White);
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                a=a-1;
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                a=a+1;
        }
        if(a<0 )
            a =4;
        else if(a>4.4 )
            a =0;
        text[a].setColor(sf::Color::Red);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            switch(a)
            {
                case 0:
                    solo(&window);
                    break;

                case 1:
                    break;

                case 2:
                    multiplayer(&window);
                    break;

                case 3:
                    break;

                case 4:
                    window.close();
                    break;

            }
        }


        window.clear();
        backgroung.Draw(&window);
        window.draw(texttitle);

        for(int i=0;i<=4;i++)
            window.draw(text[i]);

        window.display();
    }
 }
