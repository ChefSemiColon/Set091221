#include "cmp_player_weapons.h"
#include <engine.h>
#include "../game.h"
#include "../weapons/pistol.h"
#include "../weapons/assualt.h"
using namespace std;
using namespace sf;

shared_ptr<Gun> currentWeapon;
shared_ptr<Pistol> pistol;
shared_ptr<Assault> assault;

void PlayerWeapon::update(double dt) {
    if (weaponTimer < 0.0f) {
        currentWeapon = assault;
    }
    if (weaponTimer < -10.0f) {
        currentWeapon = assault;
        weaponTimer = 10.0f;
    }
    weaponTimer -= dt;
    currentWeapon->update(dt, _parent->getPosition());
}


PlayerWeapon::PlayerWeapon(Entity* p) : Component(p) {
    pistol = make_shared<Pistol>();
    assault = make_shared<Assault>();
    weaponTimer = 10.0f; 
    currentWeapon = pistol;
}

Gun::Gun()
{
}
