#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_game.h"


extern MenuScene menu;
extern GameScene game;
extern int numEnemiesAlive;
extern std::vector<std::shared_ptr<Entity>> enemies;