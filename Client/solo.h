#ifndef SOLO_H
#define SOLO_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <sstream>
#include <time.h>

#include "include/spawn.h"
#include "include/graphics/mapping.h"
#include "include/player/player.h"
#include "include/badguys/basic_shooting_ennemi.h"
#include "include/modules/modules.h"
#include "include/bonus.h"
#include "include/graphics/HUD.h"

int solo(sf::RenderWindow* p_window);
bool pause(sf::RenderWindow* p_window, bool f);

#endif // SOLO_H
