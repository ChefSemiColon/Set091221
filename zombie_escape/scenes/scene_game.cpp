//"scene_game.cpp"

#include "scene_game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_physics.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_path_follow.h"
#include "../components/cmp_basic_movement.h"
#include "../astar.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <random>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "../components/cmp_state_machine.h"
#include "../steering_states.h"
#include "../steering_decisions.h"
#include "../components/cmp_hurt_player.h"

using namespace std;
using namespace std::chrono;
using namespace sf;
shared_ptr<Entity> player;
vector<shared_ptr<Entity>> enemies;
Vector2f cameraSize;
vector<shared_ptr<PathfindingComponent>> enemyPathfinding;
sf::View view;

float radius = 399.f;
static int waveMax = 1000;
float waveStartTimer = 0.0f;

//picks a random position that is valid, spawns enemies off screen but near the player
Vector2f getRandValidPos() {
	Vector2f pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
	pos = normalize(pos);
	pos = player->getPosition() + pos * radius;
	while (pos.x == 0 && pos.y == 0) {
		pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
	}
	while (pos.x == 0 && pos.y == 0 || !ls::isOnGrid(pos) || ls::getTileAt(pos) == ls::WALL) {
		pos = Vector2f(float(rand() % 50 - 25), float(rand() % 50 - 25));
		pos = normalize(pos);
		pos = player->getPosition() + pos * radius;
	}
	return pos;
}

void setUpWave() {
	for (int i = 0; i < waveMax; ++i) {
		enemies[i]->setAlive(true);
		enemies[i]->setPosition(getRandValidPos());
	}
}

void UpdatePath(int i) {
	auto relative_pos = Vector2i(player->getPosition()) - Vector2i(ls::getOffset());
	auto tile_coord = relative_pos / (int)ls::getTileSize();
	auto char_relative = enemies[i]->getPosition() - ls::getOffset();
	auto char_tile = Vector2i(char_relative / ls::getTileSize());
	auto path = pathFind(char_tile, tile_coord);
	enemyPathfinding[i]->setPath(path);
}

void waveUpdate() {


	

}


void GameScene::Load() {
	srand(static_cast <unsigned> (time(0)));
	cameraSize = Vector2f(Engine::GetWindow().getSize());

	Physics::GetWorld()->SetGravity(b2Vec2(0, 0));
	ls::loadLevelFile("res/level_1.txt", 200.0f);


	//Player
	player = makeEntity();
	auto s = player->addComponent<ShapeComponent>();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	s->setShape<CircleShape>(10.0f);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin(10, 10);
	player->addComponent<BasicMovementComponent>();
	player->addTag("player");

	//Enemies Pool
	for (size_t n = 0; n < 1000; ++n) {
		auto enemy = makeEntity();
		enemy->setPosition(Vector2f(-100, -100));
		auto s = enemy->addComponent<ShapeComponent>();
		s->setShape<RectangleShape>(Vector2f(10.0f, 10.0f));
		s->getShape().setFillColor(Color::Green);
		enemy->setAlive(false);
		enemy->addComponent<PathfindingComponent>();

		auto sm = enemy->addComponent<StateMachineComponent>();
		sm->addState("path", make_shared<PathState>(enemy, player));
		sm->addState("seek", make_shared<SeekState>(enemy, player));
		enemy->addComponent<HurtComponent>();
		auto decision = make_shared<DistanceDecision>(
			player,
			400.0f,
			make_shared<SeekDecision>(),
			make_shared<PathDecision>());
		
		enemy->addComponent<DecisionTreeComponent>(decision);
		enemy->addTag("enemy");

		enemies.push_back(enemy);
	}

	//First wave setup
	setUpWave();
	waveUpdate();
	//Bow2D Wall Colliders
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(100.f, 100.f);
		auto e = makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(200.f, 200.f));
		e->setAlive(false);
	}
	setUpWave();
}

void GameScene::UnLoad() { player.reset(); ls::unload(); Scene::UnLoad(); }

void GameScene::Update(const double& dt) {

	if (waveStartTimer < 0) {
		//waveUpdate();
	}
	else {
		waveStartTimer -= dt;
	}
	auto tempView = View(player->getPosition(), Vector2f(cameraSize));
	tempView.zoom(10.5f);
	tempView.zoom(0.05f);
	Engine::GetWindow().setView(tempView);
	Scene::Update(dt);
}

void GameScene::Render() { ls::render(Engine::GetWindow()); Scene::Render(); }

