#include "game.h"
#include "engine.h"

MenuScene menu;
SettingsScene settings;
GameScene game;
int main() {

	Engine::Start(1920, 1080, "Zombie Escape", &menu);

}