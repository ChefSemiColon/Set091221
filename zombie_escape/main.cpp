#include "game.h"
#include "engine.h"

MenuScene menu;

int main() {

	Engine::Start(1920, 1080, "Zombie Escape", &menu);
}