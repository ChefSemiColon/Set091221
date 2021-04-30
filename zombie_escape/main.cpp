#include "game.h"
#include "engine.h"
#include "SFML/Audio.hpp"

MenuScene menu;
GameScene game;
std::vector<std::shared_ptr<Entity>> enemies;
std::vector<std::shared_ptr<Entity>> bullets;
sf::SoundBuffer musicBuffer;
sf::Sound music;
int activeBullets=0;
int enemiesKilled=0;
int numEnemiesAlive;
int main() {
	musicBuffer.loadFromFile("res/audio/BackGroundMusic.wav");
	music.setBuffer(musicBuffer);
	music.setLoop(true);
	music.setVolume(25.f);
	music.play();
	Engine::Start(1920, 1080, "Zombie Escape", &menu);

}