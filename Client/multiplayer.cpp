#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int Connect();
int StartServer();

int multiplayer()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("foughtknight.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Rejoindre une partie: R   Nouvelle partie: N", font, 20);
    text.setPosition(400-text.getGlobalBounds().width/2, 300-text.getGlobalBounds().height/2);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                Connect();
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                StartServer();
        }

        // Clear screen
        window.clear();

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

int Connect()
{
    sf::TcpSocket socket;
    socket.connect("192.168.0.35", 13700);
    return 1;
}

int StartServer()
{
    return 1;
}
