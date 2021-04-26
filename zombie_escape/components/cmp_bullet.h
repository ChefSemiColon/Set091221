#pragma once
#include "cmp_physics.h"
#include "../scenes/scene_game.h"
#include <ecm.h>

class Bullet : public Component {
protected:
	void fire() const;
	std::vector<std::shared_ptr<Entity>> enemies;

public:
	void update(double dt) override;
	void render() override {}
	explicit Bullet(Entity* p);
	Bullet() = delete;
};
