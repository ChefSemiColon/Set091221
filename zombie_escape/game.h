#pragma once

#include "scenes/scene_menu.h"
#include "scenes/scene_game.h"
#include "components/cmp_bullet.h"
#include "scenes/scene_settings.h"


extern MenuScene menu;
extern SettingsScene settings;
extern GameScene game;
extern int numEnemiesAlive;
extern std::vector<std::shared_ptr<Entity>> enemies;
extern std::vector<std::shared_ptr<Entity>> bullets;
extern int activeBullets;
extern int enemiesKilled;