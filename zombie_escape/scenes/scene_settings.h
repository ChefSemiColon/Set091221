#pragma once

#include "engine.h"

class SettingsScene : public Scene {
public:
	SettingsScene() = default;
  ~SettingsScene() override = default;

  void Load() override;

  void UnLoad() override;

  void Update(const double& dt) override;
};
