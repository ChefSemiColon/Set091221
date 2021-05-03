#include "scene_settings.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "scene_game.h"

using namespace std;
using namespace sf;
View viewRes;
vector<shared_ptr<TextComponent>> textList;
void SettingsScene::Load() {
	cout << "Settings Load \n";
	{
		auto txt = makeEntity();
		// Can't use dynamic position for menu since the game size is bigger than the window, so in smaller screen menu might get hidden
		auto bigRes = txt->addComponent<TextComponent>("1 - Resolution - 2560x1440");
		bigRes->SetPosition(Vector2f(200.0f, 100.0f));
		textList.push_back(bigRes);
		auto smallRes = txt->addComponent<TextComponent>("2 - Resolution - 1280x720");
		smallRes->SetPosition(Vector2f(200.0f, 150.0f));
		textList.push_back(smallRes);

		auto mediumRes = txt->addComponent<TextComponent>("3 - Resolution - 1920x1080");
		mediumRes->SetPosition(Vector2f(200.0f, 200.0f));
		textList.push_back(mediumRes);

		auto fullscreen = txt->addComponent<TextComponent>("4 - Fullscreen");
		textList.push_back(fullscreen);

		fullscreen->SetPosition(Vector2f(200.0f, 250.0f));
		auto backToMenu = txt->addComponent<TextComponent>("5 - Back to Menu");
		backToMenu->SetPosition(Vector2f(200.0f, 300.0f));
		textList.push_back(backToMenu);

	}
	viewRes.setSize(Vector2f(Engine::GetWindow().getSize()));
	Engine::GetWindow().setView(viewRes);
	setLoaded(true);
}
void SettingsScene::UnLoad() { textList.clear();  Scene::UnLoad(); }
void SettingsScene::Update(const double& dt) {
	// Change resolution based on user input
	if (Keyboard::isKeyPressed(Keyboard::Num1)) {

		Engine::GetWindow().create(VideoMode(2560, 1440, VideoMode::getDesktopMode().bitsPerPixel), "Zombie Esscape", Style::Close);



		View visArea(Vector2f(640, 360), Vector2f(2560, 1440));
		Engine::GetWindow().setView(visArea);
		auto scale = 720.f / Engine::GetWindow().getView().getSize().y;
		View tempZoom = Engine::GetWindow().getView();
		tempZoom.zoom(scale);
		Engine::GetWindow().setView(tempZoom);

	}
	if (Keyboard::isKeyPressed(Keyboard::Num2)) {

		Engine::GetWindow().create(VideoMode(1280, 720, VideoMode::getDesktopMode().bitsPerPixel), "Zombie Esscape", Style::Close);

		auto scale = 720.f / Engine::GetWindow().getView().getSize().y;

		View visArea(Vector2f(640, 360), Vector2f(1280, 720));
		Engine::GetWindow().setView(visArea);

		View tempZoom = Engine::GetWindow().getView();
		tempZoom.zoom(scale);
		Engine::GetWindow().setView(tempZoom);

	}
	if (Keyboard::isKeyPressed(Keyboard::Num3)) {

		Engine::GetWindow().create(VideoMode(1920, 1080, VideoMode::getDesktopMode().bitsPerPixel), "Zombie Esscape", Style::Close);

		auto scale = 720.f / Engine::GetWindow().getView().getSize().y;

		View visArea(Vector2f(960, 540), Vector2f(1920, 1080));
		Engine::GetWindow().setView(visArea);

		View tempZoom = Engine::GetWindow().getView();
		tempZoom.zoom(scale);
		Engine::GetWindow().setView(tempZoom);


	}
	if (Keyboard::isKeyPressed(Keyboard::Num5)) {
		Engine::ChangeScene(&menu);
	}
	auto spacing = 0.0f;
	for (auto& txt : textList) {
		txt->SetPosition(Vector2f(Engine::GetWindow().getView().getCenter().x, Engine::GetWindow().getView().getCenter().y + spacing));
		spacing += 50.f;
	}











	Scene::Update(dt);
}
