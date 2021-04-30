#include "game.h"
#include "engine.h"

MenuScene menu;
GameScene game;
std::vector<std::shared_ptr<Entity>> enemies;
std::vector<std::shared_ptr<Entity>> bullets;
int activeBullets=0;
int enemiesKilled=0;
int numEnemiesAlive;
int main() {

	Engine::Start(1920, 1080, "Zombie Escape", &menu);

}