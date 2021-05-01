#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MenuScene::Load() {
  cout << "Menu Load \n";
  {
    auto txt = makeEntity();
    // Can't use dynamic position for menu since the game size is bigger than the window, so in smaller screen menu might get hidden
    auto startGameMenu = txt->addComponent<TextComponent>("1 - Start Game");
    startGameMenu->SetPosition(sf::Vector2f(200.0f, 100.0f));
    auto settingsMenu = txt->addComponent<TextComponent>("2 - Settings");
    settingsMenu->SetPosition(sf::Vector2f(200.0f, 150.0f));
    auto leaveTheGame = txt->addComponent<TextComponent>("ESC - Leave the game");
    leaveTheGame->SetPosition(sf::Vector2f(200.0f, 200.0f));

  }
  setLoaded(true);
}
void MenuScene::UnLoad() { Scene::UnLoad(); }
void MenuScene::Update(const double& dt) {
     // Start game or go to settings based on user input
     if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
         Engine::ChangeScene(&game);
     }
     if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
         Engine::ChangeScene(&settings);
     }
	 	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		Engine::GetWindow().close();
	}
  Scene::Update(dt);
}
void MenuScene::Render() { Scene::Render(); }
