#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;


MenuScene menu;
SteeringScene steeringScene;
PathfindingScene pathfindingScene;
int main() {
  Engine::Start(1280, 720, "Platformer",&menu);
}