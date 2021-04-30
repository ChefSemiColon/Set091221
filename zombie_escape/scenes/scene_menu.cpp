#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
	cout << "Menu Load \n";

	auto txt = makeEntity();
	auto t = txt->addComponent<TextComponent>("			MAIN MENU");
	//Scene::Load();
}
void MenuScene::UnLoad() { Scene::UnLoad(); }
void MenuScene::Update(const double& dt) {
	// cout << "Menu Update "<<dt<<"\n";
	if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
		Engine::GetWindow().setSize(Vector2u(1280, 720));
		Engine::ChangeScene(&game);
	}
	if (sf::Keyboard::isKeyPressed(Keyboard::Num0)) {
		Engine::GetWindow().setSize(Vector2u(1280, 720));

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		Engine::GetWindow().close();
	}
	Scene::Update(dt);
}
void MenuScene::Render() { Scene::Render(); }
