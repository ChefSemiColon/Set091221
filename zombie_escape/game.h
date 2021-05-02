#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_game.h"
#include "components/cmp_bullet.h"
#include "scenes/scene_settings.h"
#include "scenes/scene_dead.h"


extern MenuScene menu;
extern SettingsScene settings;
extern GameScene game;
extern DeadScene gameOver;
extern int numEnemiesAlive;
extern std::vector<std::shared_ptr<Entity>> enemies;
extern std::vector<std::shared_ptr<Entity>> bullets;
extern int activeBullets;
extern int enemiesKilled;
extern int enemiesKilledTotal;