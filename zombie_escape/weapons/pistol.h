#pragma once
#include "../components/cmp_player_weapons.h"
#include <engine.h>

class Pistol : public Gun {
public:
	float fireRate = 0.29f;
	float timer = fireRate;
	Pistol();
	void update(double dt, sf::Vector2f pos);
	void render() override {}

};