#include "game.h"
#include "engine.h"

MenuScene menu;
GameScene game;
int main() {

	Engine::Start(1920, 1080, "Zombie Escape", &menu);

}