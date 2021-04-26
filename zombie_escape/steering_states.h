//steering_states.h
#pragma once

#include "steering.h"
#include "components/cmp_state_machine.h"

class PathState : public State
{
private:
    Path _path;
    size_t _index = 0;
    double _elapsed = 0.0;
public:
    PathState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : _path(owner.get(), player.get(), 400.0f){ }
    void execute(Entity*, double) noexcept override;
};

class SeekState : public State
{
private:
    Seek _steering;
public:
    SeekState(std::shared_ptr<Entity> owner, std::shared_ptr<Entity> player) : _steering(owner.get(), player.get(), 100.0f) { }
    void execute(Entity*, double) noexcept override;
};
