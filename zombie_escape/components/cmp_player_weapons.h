#pragma once
#include "cmp_physics.h"
#include "../scenes/scene_game.h"
#include <ecm.h>

class PlayerWeapon : public Component {
protected:
	void fire() const;
	std::vector<std::shared_ptr<Entity>> enemies;

public:
	void update(double dt) override;
	void render() override {}
	explicit PlayerWeapon(Entity* p);
	PlayerWeapon() = delete;
};
