#include "cmp_player_weapons.h"
#include <engine.h>
#include "../game.h"
using namespace std;
using namespace sf;

void PlayerWeapon::update(double dt) {
    
    for(int i=0; i<numEnemiesAlive;++i)
        if (length(enemies[i]->getPosition() - _parent->getPosition()) < 25.0) {
            enemies[i]->setPosition({ -1000,-1000 });
            enemies[i]->setAlive(false);
            _parent->setPosition({ -1000,-1000 });
            _parent->setAlive(false);

        }
    
}

PlayerWeapon::PlayerWeapon(Entity* p) : Component(p) {}
