//"steering.cpp"
#include "steering.h"
#include "LevelSystem.h"
using namespace sf;

SteeringOutput Seek::getSteering() const noexcept{
    SteeringOutput steering;
    steering.direction = _target->getPosition() - _character->getPosition();
    steering.direction = normalize(steering.direction);
    steering.direction *= _maxSpeed;
    steering.rotation = 0.0f;
    return steering;
}

std::vector<Vector2i> Path::getPath()
{
    auto relative_pos = Vector2i(_target->getPosition()) - Vector2i(ls::getOffset());
    auto tile_coord = relative_pos / (int)ls::getTileSize();
    auto char_relative = _character->getPosition() - ls::getOffset();
    auto char_tile = Vector2i(char_relative / ls::getTileSize());
    return pathFind(char_tile, tile_coord);
}
