#pragma once
#include "cmp_physics.h"
#include "../scenes/scene_game.h"
#include <ecm.h>

class PlayerWeapon : public Component {
protected:
	std::vector<std::shared_ptr<Entity>> enemies;
	float weaponTimer;
public:
	void update(double dt) override;
	void render() override {}
	explicit PlayerWeapon(Entity* p);
	PlayerWeapon() = delete;
};

class Gun {
public:
	Gun();
	virtual void update(double dt, sf::Vector2f pos) = 0;
	virtual void render() = 0;
};