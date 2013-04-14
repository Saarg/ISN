#include "multiplayer.h"

int multiplayer(sf::RenderWindow* p_window)
{
    sf::TcpSocket socket;
    server server;
    sf::Thread thread(&server::Run, &server);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("foughtknight.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Tentative de connection", font, 50);
    text.setPosition(400-text.getGlobalBounds().width/2, 300-text.getGlobalBounds().height/2);
    p_window->clear();

    // Draw the string
    p_window->draw(text);

    // Update the window
    p_window->display();
    while(socket.connect("88.161.60.243", 25565) != sf::Socket::Done)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            return EXIT_SUCCESS;
    }

    sf::Packet PacketID;
    socket.receive(PacketID);
    // Extract the variables contained in the packet
    int ID;
    if (PacketID >> ID)
    {
        text.setString("En attante de partenaire...");
        p_window->clear();

        // Draw the string
        p_window->draw(text);

        // Update the window
        p_window->display();
        PacketID.clear();
        std::string pseudo = "jean";
        PacketID << int(1) << ID << pseudo << 0x00ff0000;
        socket.send(PacketID);
        PacketID.clear();
        socket.receive(PacketID);
        // Extract the variables contained in the packet
        int ID2;
        int couleur;
        if (PacketID >> ID2 >> pseudo >> couleur)
        {
            text.setString("Vous allez jouer contre " + pseudo);
            p_window->clear();

            // Draw the string
            p_window->draw(text);

            // Update the window
            p_window->display();
        }
    }

    while (p_window->isOpen())
    {
        sf::Event event;
        while (p_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                p_window->close();
        }
        p_window->clear();

        // Draw the string
        p_window->draw(text);

        // Update the window
        p_window->display();
    }

    return EXIT_SUCCESS;
}
