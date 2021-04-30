#pragma once
#include "../components/cmp_player_weapons.h"
#include <engine.h>

class Assault : public Gun {
public:
	float fireRate = 0.11f;
	float timer = fireRate;
	Assault();
	void update(double dt, sf::Vector2f pos) ;
	void render() override {}

};