//steering_states.cpp
#include "steering_states.h"
#include "components/cmp_sprite.h"
#include "components/cmp_path_follow.h"
#include "LevelSystem.h" 
#define ls LevelSystem

using namespace sf;
    shared_ptr<PathfindingComponent> pc;
void PathState::execute(Entity* owner, double dt) noexcept {

    vector<Vector2i> p = _path.getPath();
    _elapsed += dt;
    if (_elapsed >= 0.1) {
        _elapsed = 0.0;
        if (_index < p.size()) {
            // Could do this in a single line - expanded for clarity
            float new_x = ls::getOffset().x + p[_index].x * ls::getTileSize();
            float new_y = ls::getOffset().y + p[_index].y * ls::getTileSize();
            owner->setPosition(Vector2f(new_x, new_y));
            ++_index;
        }
    }
}

void SeekState::execute(Entity* owner, double dt) noexcept {
    auto s = owner->get_components<ShapeComponent>();
    s[0]->getShape().setFillColor(Color::Green);
    auto output = _steering.getSteering();
    owner->setPosition(owner->getPosition() + (output.direction * (float)dt));
}