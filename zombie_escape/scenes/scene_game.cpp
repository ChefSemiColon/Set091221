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
#include "../game.h"
#include "../components/cmp_bullet.h"
using namespace std;
using namespace std::chrono;
using namespace sf;
shared_ptr<Entity> player;
vector<shared_ptr<Entity>> enemies;
vector<shared_ptr<Entity>> bullets;
Vector2f cameraSize;
shared_ptr<PathfindingComponent> ai;
sf::View view;

float radius = 405.f;
static int waveMax = 10;
float waveStartTimer = 20.0f;
bool spawnOverTime = false;
float spawnOverTimeTimerSet = 5.0f;
float spawnOverTimeTimer = 0.0f;
float OneSecondTimer = 1.0f;
int numEnemiesAlive;
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

void setUpWave(int enemiesAliveAlready, int numToSpawn) {
	numToSpawn = numToSpawn + enemiesAliveAlready;
	for (enemiesAliveAlready; enemiesAliveAlready < numToSpawn; ++enemiesAliveAlready) {
		enemies[enemiesAliveAlready]->setAlive(true);
		enemies[enemiesAliveAlready]->setPosition(getRandValidPos());
		numEnemiesAlive++;
	}
}

void waveUpdate(const double& dt) {
	if (numEnemiesAlive == 0) {
		auto waveMaxTemp = waveMax + (waveMax / 2);
		waveMaxTemp <= 1000 ? waveMax = waveMaxTemp : waveMax = 1000;
		waveStartTimer = 7.0f;
		spawnOverTime = true;
		spawnOverTimeTimer = spawnOverTimeTimerSet;
	}

	if (OneSecondTimer < 0) {
		if (spawnOverTime) {
			int enemiesToSpawnNow = waveMax / spawnOverTimeTimerSet;
			setUpWave(numEnemiesAlive, enemiesToSpawnNow);
			spawnOverTimeTimer -= dt;
			if (spawnOverTimeTimer <= 0) {
				spawnOverTime = false;
			}
			OneSecondTimer = 1.0f;
		}
	}
	else {
		OneSecondTimer -= dt;
	}
}


void GameScene::Load() {
	srand(static_cast <unsigned> (time(0)));

	cameraSize = Vector2f(Engine::GetWindow().getView().getSize());
	wallSprite = make_shared<Texture>();
	wallSprite->loadFromFile("res/img/Brick_Wall.png");
	floorSprite = make_shared<Texture>();
	floorSprite->loadFromFile("res/img/ground.png");
	playerSprite = make_shared<Texture>();
	playerSprite->loadFromFile("res/img/player.png");
	zombieSprite = make_shared<Texture>();
	zombieSprite->loadFromFile("res/img/zombie.png");
	bulletSprite = make_shared<Texture>();
	bulletSprite->loadFromFile("res/img/bullet.png");

	Physics::GetWorld()->SetGravity(b2Vec2(0, 0));
	ls::loadLevelFile("res/level_1.txt", 200.0f);


		auto floor = ls::findTiles(ls::EMPTY);
		for (auto f : floor) {
			auto pos = ls::getTilePosition(f);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->setTexure(floorSprite);


		}
		//Bow2D Wall Colliders
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls) {
			auto pos = ls::getTilePosition(w);

			auto e = makeEntity();
			e->setPosition(pos);
			e->addComponent<PhysicsComponent>(false, Vector2f(200.f, 200.f));
			auto s = e->addComponent<SpriteComponent>();
			s->setTexure(wallSprite);

			//e->setAlive(false);
		}
	}

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
	for (size_t n = 0; n < 2000; ++n) {
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
			415.0f,
			make_shared<SeekDecision>(),
			make_shared<PathDecision>());

		enemy->addComponent<DecisionTreeComponent>(decision);
		enemy->addTag("enemy");

		enemies.push_back(enemy);
	}

	//Bullet Pool
	{
		for (size_t n = 0; n < 500; ++n) {
			auto bullet = makeEntity();
			bullet->setPosition({ -1000,-1000 });
			bullet->setAlive(false);
			auto s = bullet->addComponent<ShapeComponent>();
			s->setShape<RectangleShape>(Vector2f(10.0f, 10.0f));
			s->getShape().setFillColor(Color::White);
			bullet->addComponent<Bullet>();
		}
	}


	//First wave setup
	setUpWave(0, 10);

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
}

void GameScene::UnLoad() { player.reset(); ls::unload(); Scene::UnLoad(); }

void GameScene::Update(const double& dt) {
	waveUpdate(dt);




	// Calculations for the player to point to the mouse position
	Vector2f playerPos = player->getPosition();
	Vector2i mousePos = Mouse::getPosition(Engine::GetWindow());
	Vector2f mousePos2 = Engine::GetWindow().mapPixelToCoords(mousePos);
	float dx = playerPos.x - mousePos2.x;
	float dy = playerPos.y - mousePos2.y;
	float rotation = (atan2(dy, dx)) * 180 / M_PI;
	player->setRotation(rotation + 180);

	// Calculation for the zombies to point towards the player
	for (int i = 0; i < enemies.size(); i++) {
		Vector2f zombiePos = enemies[i]->getPosition();
		Vector2f playerPos = player->getPosition();
		float dx = zombiePos.x - playerPos.x;
		float dy = zombiePos.y - playerPos.y;
		float rotation = (atan2(dy, dx)) * 180 / M_PI;
		enemies[i]->setRotation(rotation + 180);
	}

	auto scale = (720.f / cameraSize.y)*0.5f;
	auto tempView = View(player->getPosition(), Vector2f(cameraSize));
	tempView.zoom(scale);
	Engine::GetWindow().setView(tempView);
	Scene::Update(dt);
}

void GameScene::Render() { ls::render(Engine::GetWindow()); Scene::Render(); }

