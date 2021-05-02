#include"cmp_bullet.h"
#include <engine.h>
#include "../game.h"
#include "LevelSystem.h"
using namespace std;
using namespace sf;

void Bullet::fire(Vector2f dir, Vector2f pos){

    _parent->setAlive(true);
    _parent->setPosition(pos);
    bulletVel = dir * bulletSpeed;
    activeBullets++;
}

void Bullet::update(double dt) {
    if (_parent->isAlive()) {

        auto pos = _parent->getPosition() + bulletVel * float(dt);
        if (ls::getTileAt(pos + Vector2f(10.5f, 10.5f)) != ls::WALL && ls::getTileAt(pos - Vector2f(10.5f, 10.5f)) != ls::WALL) {
        _parent->setPosition(pos);
        for (int i = 0; i < numEnemiesAlive; ++i)
            if (length(enemies[i]->getPosition() - _parent->getPosition()) < 20.0f) {
                enemies[i]->setPosition({ -1000.0f,-1000.0f });
                enemies[i]->setVisible(false);
                enemies[i]->setAlive(false);
                _parent->setPosition({ -1000.0f,-1000.0f });
                _parent->setAlive(false);
                _parent->setVisible(false);
                enemiesKilled++;
                break;
            }
        }
        else {
            _parent->setAlive(false);
            _parent->setVisible(false);
        }

    }
}

Bullet::Bullet(Entity* p) : Component(p) {}
