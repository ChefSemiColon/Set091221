#pragma once

#include "engine.h"

class DeadScene : public Scene {
public:
	DeadScene() = default;
  ~DeadScene() override = default;

  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;
};
