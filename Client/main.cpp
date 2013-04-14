#include "solo.h"
#include "multiplayer.h"
#include <SFML/Graphics.hpp>


 int main()
 {
     // Create the main window
     sf::RenderWindow window(sf::VideoMode(800, 900), "SFML window");   //creation d'une fenetre de 800/900
     window.setFramerateLimit(60);                                      //limite le programme a 60 fps

     sf::Font font;
     if (!font.loadFromFile("foughtknight.ttf"))                        //police d'écriture
         return EXIT_FAILURE;

     sf::Text texttitle("title", font, 50);

     sf::Text text[5];
     text[0]=sf::Text("solo", font, 50 );
     text[1]=sf::Text("duel", font, 50 );
     text[2]=sf::Text("multijoueur", font, 50 );
     text[3]=sf::Text("options", font, 50 );
     text[4]=sf::Text("quitter", font, 50 );                            //tableau de caractere

     int a(0);                                                          //a ---> la variable permettant de naviguer dans le menu
     bool quit = false;                                                //quit permettras de fermer le programme

     texttitle.setPosition(400-(texttitle.getGlobalBounds().width)/2, 100);

     text[0].setPosition(400-(text[0].getGlobalBounds().width)/2, 250);
     text[1].setPosition(400-(text[1].getGlobalBounds().width)/2, 300);
     text[2].setPosition(400-(text[2].getGlobalBounds().width)/2, 350);
     text[3].setPosition(400-(text[3].getGlobalBounds().width)/2, 400);
     text[4].setPosition(400-(text[4].getGlobalBounds().width)/2, 450); //position des textes



     // Start the game loop
     while (window.isOpen())
     {
         // Process events
         sf::Event event;
         while (window.pollEvent(event))
         {
             // Close window : exit
             if (event.type == sf::Event::Closed or quit )
                 window.close();


            text[a].setColor(sf::Color::White);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                    a=a-1;
            }
              else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                     a=a+1;
            }
            if(a<0 )
            {
            a =4;
            }
            else if(a>4.4 )
            {
            a =0;
            }
            text[a].setColor(sf::Color::Red);


             window.clear();
             window.draw(texttitle);

             for(int i=0;i<=4;i++){
                window.draw(text[i]);
             }

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
                        quit=true;
                        break;

                }

            }

        }

        window.display();
     }
 }
