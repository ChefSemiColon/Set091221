#include "../components/cmp_player_weapons.h"
#include "pistol.h"
#include <engine.h>
#include <LevelSystem.h>
#include "../components/cmp_bullet.h"
#include "../game.h"
using namespace std;
using namespace sf; 



Pistol::Pistol() : timer(fireRate) {}

void Pistol::update(double dt, Vector2f pos){
	if (timer < 0.0f) {
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i temp = (Mouse::getPosition(Engine::GetWindow()));
			Vector2f temp2 = Engine::GetWindow().mapPixelToCoords(temp);
			Vector2f dir = normalize(temp2 - pos);
			timer = fireRate;
			bullets[activeBullets]->get_components<Bullet>()[0]->fire(dir, pos);
		}
	}
	timer -= dt;
}

