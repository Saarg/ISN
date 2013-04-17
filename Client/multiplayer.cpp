#include "multiplayer.h"

void run(sf::RenderWindow* p_window, sf::TcpSocket* socket, int id);

int multiplayer(sf::RenderWindow* p_window)
{
    sf::TcpSocket socket;

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
        run(p_window, &socket, ID);
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

void run(sf::RenderWindow* p_window, sf::TcpSocket* socket, int id)
{
    bool Run = true;
    socket->setBlocking(false);

    std::vector<vaisseau*> entity_tab;
    std::vector<missile*> missile_tab;

    entity_tab.push_back(new player(&missile_tab, &entity_tab));
    entity_tab.push_back(new player(&missile_tab, &entity_tab));

    sf::Packet packet;

    while(Run and p_window->isOpen())
    {
        sf::Event event;
        while (p_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                p_window->close();
        }

        if(sf::Mouse::getPosition(*p_window).x-10 > 0 and sf::Mouse::getPosition(*p_window).y-10 > 0 and sf::Mouse::getPosition(*p_window).y < 900 and sf::Mouse::getPosition(*p_window).x < 800)
            entity_tab[0]->setPosition(sf::Mouse::getPosition(*p_window).x-10, sf::Mouse::getPosition(*p_window).y-10);

        packet.clear();
        packet << int(2) << id << (int) (entity_tab[id-1]->getPosition().x) << (int) (entity_tab[id-1]->getPosition().y);
        socket->send(packet);

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
                    }

                }
            }
        }
        for(std::vector<vaisseau*>::size_type i = 0 ; i < entity_tab.size() ; i++)
        {
            entity_tab.at(i)->Draw(p_window);
        }

        p_window->display();
    }
}
