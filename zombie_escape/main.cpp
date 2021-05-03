#include "game.h"
#include "engine.h"

MenuScene menu;
SettingsScene settings;
GameScene game;
int main() {

	musicBuffer.loadFromFile("res/audio/BackGroundMusic.wav");
	music.setBuffer(musicBuffer);
	music.setLoop(true);
	music.setVolume(5.f);
	music.play();
	Engine::Start(1280, 720, "Zombie Escape", &menu);

}