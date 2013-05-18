#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "server.h"
#include "include/network/PacketList.h"
#include "include/graphics/mapping.h"

int multiplayer(sf::RenderWindow* p_window);

#endif // MULTIPLAYER_H
