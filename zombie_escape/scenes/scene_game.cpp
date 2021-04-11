//"scene_game.cpp"

#include "scene_game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_basic_movement.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;
using namespace sf;
shared_ptr<Entity> player;
Vector2f cameraSize;
void GameScene::Load() {
    Physics::GetWorld()->SetGravity(b2Vec2(0,0));
    ls::loadLevelFile("res/level_1.txt", 200.0f);
    player = makeEntity();
    auto s = player->addComponent<ShapeComponent>();
    player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
    s->setShape<CircleShape>(10.0f);
    s->getShape().setFillColor(Color::Red);
    s->getShape().setOrigin(10,10);
    player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));

    auto walls = ls::findTiles(ls::WALL);
    for (auto w : walls) {
        auto pos = ls::getTilePosition(w);
        pos += Vector2f(100.f, 100.f);
        auto e = makeEntity();
        e->setPosition(pos);
        e->addComponent<PhysicsComponent>(false, Vector2f(200.f, 200.f));
    }
    cameraSize = Vector2f(Engine::GetWindow().getSize());
}

void GameScene::UnLoad() { ls::unload(); Scene::UnLoad(); }

void GameScene::Update(const double& dt) {
    Engine::GetWindow().setView(View(player->getPosition(), Vector2f(cameraSize)));
Scene::Update(dt); }

void GameScene::Render() { ls::render(Engine::GetWindow()); Scene::Render(); }