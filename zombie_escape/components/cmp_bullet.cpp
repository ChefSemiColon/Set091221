#include"cmp_bullet.h"
#include <engine.h>
#include "../game.h"
using namespace std;
using namespace sf;

void Bullet::update(double dt) {

    for (int i = 0; i < numEnemiesAlive; ++i)
        if (length(enemies[i]->getPosition() - _parent->getPosition()) < 25.0) {
            enemies[i]->setPosition({ -1000,-1000 });
            enemies[i]->setAlive(false);
            _parent->setPosition({ -1000,-1000 });
            _parent->setAlive(false);

        }

}

Bullet::Bullet(Entity* p) : Component(p) {}
