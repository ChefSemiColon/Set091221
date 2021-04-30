#pragma once
#include "cmp_physics.h"
#include "../scenes/scene_game.h"
#include <ecm.h>

class Bullet : public Component {
protected:

	float bulletSpeed = 300.f;
	sf::Vector2f bulletVel;
public:
	void fire(sf::Vector2f dir, sf::Vector2f pos);
	void update(double dt) override;
	void render() override {}
	explicit Bullet(Entity* p);
	Bullet() = delete;
};
