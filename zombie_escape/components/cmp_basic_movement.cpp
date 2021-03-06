//"cmp_basic_movement.cpp"
#include "cmp_basic_movement.h"
#include <SFML/Window/Keyboard.hpp>
#include <engine.h>
#include <LevelSystem.h>
using namespace sf;
using namespace std;

// Checks keyboard and moves the player.
void BasicMovementComponent::update(double dt) {
	Vector2f direction(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction.x -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction.x += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction.y -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction.y += 1.0f;
	}
	move(normalize(direction) * _speed * (float)dt);
}

// Initialises the component.
BasicMovementComponent::BasicMovementComponent(Entity* p)
	: _speed(100.0f), Component(p) {}

// Checks if the proposed move is valid.
bool BasicMovementComponent::validMove(const sf::Vector2f& pos) {
	return (ls::getTileAt(pos + Vector2f(10.5f, 10.5f)) != ls::WALL && ls::getTileAt(pos - Vector2f(10.5f, 10.5f)) != ls::WALL);
}


// Moves the component's parent.
void BasicMovementComponent::move(const sf::Vector2f& p) {
	auto new_pos = _parent->getPosition() + p;
	if (validMove(new_pos)) {
		_parent->setPosition(new_pos);
	}
}

// Moves the component's parent.
void BasicMovementComponent::move(float x, float y) {
	move(Vector2f(x, y));
}