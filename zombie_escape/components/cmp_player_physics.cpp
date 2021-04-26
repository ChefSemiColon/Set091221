#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;


void PlayerPhysicsComponent::update(double dt) {

  const auto pos = _parent->getPosition();

  //Teleport to start if we fall off map.

  if (Keyboard::isKeyPressed(Keyboard::Left)) {
      impulse({ -(float)(dt * _groundspeed), 0 });
  }
 

  if (Keyboard::isKeyPressed(Keyboard::Right)) {
      if (getVelocity().x < _maxVelocity.x)
          impulse({ (float)(dt * _groundspeed), 0 });
  }


      if (Keyboard::isKeyPressed(Keyboard::Up)) {
          if (getVelocity().y > -_maxVelocity.y)
              impulse({0, -(float)(dt * _groundspeed)});

      }

      if (Keyboard::isKeyPressed(Keyboard::Down)) {
          if (getVelocity().y < _maxVelocity.y)
              impulse({ 0,(float)(dt * _groundspeed)});
      }
  

      dampen({ 0.9f, 0.9f });

  // Clamp velocity.
  auto v = getVelocity();
  v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
  v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
  setVelocity(v);

  PhysicsComponent::update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
                                               const Vector2f& size)
    : PhysicsComponent(p, true, size) {
  _size = sv2_to_bv2(size, true);
  _maxVelocity = Vector2f(200.f, 200.f);
  _groundspeed = 30.f;
  _grounded = false;
  _body->SetSleepingAllowed(false);
  _body->SetFixedRotation(true);
  //Bullet items have higher-res collision detection
  _body->SetBullet(true);
}
