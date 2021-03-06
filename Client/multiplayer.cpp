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
    while(socket.connect(" 88.161.60.243", 25565) != sf::Socket::Done)
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
        std::cout << ID << std::endl;
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

        int test = 0;
        while(test != 1234)
        {
            PacketID.clear();
            socket.receive(PacketID);
            // Extract the variables contained in the packet
            if (PacketID >> test){run(p_window, &socket, ID);}
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

void run(sf::RenderWindow* p_window, sf::TcpSocket* socket, int id)
{
    bool Run = true;
    socket->setBlocking(false);

    mapping backgroung;

    std::vector<vaisseau*> entity_tab;
    std::vector<missile*> missile_tab;

    entity_tab.push_back(new player(&missile_tab, &entity_tab));
    entity_tab.push_back(new player(&missile_tab, &entity_tab));

    sf::Packet packet;

    player* p =  (player*) (entity_tab[id-1]);

    while(Run and p_window->isOpen())
    {
        sf::Event event;
        while (p_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                p_window->close();
            else if(((event.type == sf::Event::MouseButtonPressed) or (event.type == sf::Event::MouseButtonReleased)) and (event.mouseButton.button == sf::Mouse::Left))
            {
                player* p = (player*) (entity_tab[id-1]);
                p->shooting(sf::Mouse::isButtonPressed(sf::Mouse::Left));
                packet.clear();
                packet << int(3) << id << sf::Mouse::isButtonPressed(sf::Mouse::Left);
                socket->send(packet);
            }
        }
        int rotation = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            rotation = p->acceleration(2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            rotation = p->acceleration(3);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            rotation = p->acceleration(0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            rotation = p->acceleration(1);

        if(p->getSpeed().x != 0 or p->getSpeed().y != 0)
        {
            packet.clear();
            packet << int(2) << id << (int) (p->getPosition().x) << (int) (p->getPosition().y);
            socket->send(packet);
        }
        if(rotation != 0)
        {
            packet.clear();
            packet << int(5) << id << (int) (p->getRotation());
            socket->send(packet);
        }

        packet.clear();
        socket->receive(packet);
        int ID;
        if (packet >> ID)
        {
            packet.clear();
            socket->setBlocking(true);
            socket->receive(packet);
            socket->setBlocking(false);
            if(ID == 1)
            {
                int P_ID, couleur;
                std::string pseudo;
                if(packet >> P_ID >> pseudo >> couleur)
                    std::cout << P_ID << " " << pseudo << " joue contre vous" << std::endl;
                else
                    std::cout << "packet " << ID << " impossible a lire" << std::endl;
            }
            else if (ID == 2)
            {
                int P_ID, X, Y;
                if(packet >> P_ID >> X >> Y)
                    entity_tab[P_ID-1]->setPosition(X, Y);
                else
                    std::cout << "packet " << ID << " impossible a lire" << std::endl;
            }
            else if (ID == 3)
            {
                int P_ID;
                bool fire;
                if(packet >> P_ID >> fire)
                {
                    player* p = (player*) (entity_tab[P_ID-1]);
                    p->shooting(fire);
                }
                else
                    std::cout << "packet " << ID << " impossible a lire" << std::endl;
            }
            else if (ID == 4)
            {
                int X, S_X, S_Y, life;
                if(packet >> X >> S_X >> S_Y >> life)
                {
                    std::vector<sf::Vector2f> shots;
                    shots.push_back(sf::Vector2f(0, 10));
                    entity_tab.push_back(new vaisseau(&missile_tab, &entity_tab, shots, sf::Vector2f(S_X, S_Y), sf::Color::Red, life));
                    entity_tab[entity_tab.size()-1]->setPosition(X, 0);
                }
                else
                    std::cout << "packet " << ID << " impossible a lire" << std::endl;
            }
            else if (ID == 5)
            {
                int P_ID, angle;
                if(packet >> P_ID >> angle)
                    entity_tab[P_ID-1]->setRotation(angle-entity_tab[P_ID-1]->getRotation()
                                                    );
                else
                    std::cout << "packet " << ID << " impossible a lire" << std::endl;
            }
            else{}
        }
        else
        {
            //std::cout << "lecture de l'id du packet impossible!" << std::endl;
        }


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
