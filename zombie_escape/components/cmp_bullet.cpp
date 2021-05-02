#include"cmp_bullet.h"
#include "SFML/Audio.hpp"
#include <engine.h>
#include "../game.h"
#include "LevelSystem.h"
using namespace std;
using namespace sf;
SoundBuffer buffer;
Sound gunShot;

void Bullet::fire(Vector2f dir, Vector2f pos){
    int randomNum = rand() % 3;

    switch (randomNum) {
    case 0:
        buffer.loadFromFile("res/audio/Bang1.wav");
        break;
    case 1:
        buffer.loadFromFile("res/audio/Bang2.wav");
        break;
    case 2:
        buffer.loadFromFile("res/audio/Bang3.wav");
        break;
    }
    gunShot.setBuffer(buffer);
    gunShot.play();
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
            if (length(enemies[i]->getPosition() - _parent->getPosition()) < 35.0f) {
                enemies[i]->setPosition({ -1000.0f,-1000.0f });
                enemies[i]->setVisible(false);
                enemies[i]->setAlive(false);
                _parent->setPosition({ -1000.0f,-1000.0f });
                _parent->setAlive(false);
                _parent->setVisible(false);
                enemiesKilled++;
                enemiesKilledTotal++;
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
