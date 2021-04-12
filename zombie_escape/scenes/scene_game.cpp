//"scene_game.cpp"

#include "scene_game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_path_follow.h"
#include "../astar.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;
using namespace sf;
shared_ptr<Entity> player;
Vector2f cameraSize;
shared_ptr<PathfindingComponent> ai;
sf::View view;

float radius = 400.f;

//picks a random position that is valid, spawns enemies off screen but near the player
Vector2f getRandValidPos() {

	Vector2f pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
	pos = normalize(pos);
	pos = player->getPosition() + pos * radius;
	while (pos.x == 0 && pos.y == 0) {
		pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
	}
	while (pos.x == 0 && pos.y == 0||!ls::isOnGrid(pos) || ls::getTileAt(pos) == ls::WALL) {
		pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
			pos = normalize(pos);
			pos = player->getPosition() + pos * radius;
	}
	return pos;
}

void GameScene::Load() {
	//Player
	Physics::GetWorld()->SetGravity(b2Vec2(0, 0));
	ls::loadLevelFile("res/level_1.txt", 200.0f);
	player = makeEntity();
	auto s = player->addComponent<ShapeComponent>();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(10, 10);
	player->addComponent<PlayerPhysicsComponent>(Vector2f(20.f, 20.f));

	//Enemies
	for (size_t n = 0; n < 100; ++n) {
	    auto enemy = makeEntity();
	    enemy->setPosition(Vector2f(getRandValidPos()));
	    auto s = enemy->addComponent<ShapeComponent>();
	    s->setShape<RectangleShape>(Vector2f(10.0f, 10.0f));
	    s->getShape().setFillColor(Color::Green);
	    enemy->addComponent<PathfindingComponent>();
	}


	//Bow2D Wall Colliders
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(100.f, 100.f);
		auto e = makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(200.f, 200.f));
	}

	cameraSize = Vector2f(Engine::GetWindow().getSize());
	srand(static_cast <unsigned> (time(0)));
}

void GameScene::UnLoad() { player.reset(); ls::unload(); Scene::UnLoad(); }

void GameScene::Update(const double& dt) {
	auto tempView = View(player->getPosition(), Vector2f(cameraSize));
	tempView.zoom(10.5f);
	//tempView.zoom(0.05f);
	Engine::GetWindow().setView(tempView);
	Scene::Update(dt);
}

void GameScene::Render() { ls::render(Engine::GetWindow()); Scene::Render(); }