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
    //float gameWidth = Engine::getWindowSize().x;
    //float gameHeight = Engine::getWindowSize().y;
    auto startGameMenu = txt->addComponent<TextComponent>("Start Game");
    //startGameMenu->SetPosition(sf::Vector2f((gameWidth / 1.5f), (gameHeight / 1.5f)));
    startGameMenu->SetPosition(sf::Vector2f(200.0f, 100.0f));
    auto settingsMenu = txt->addComponent<TextComponent>("Settings");
    settingsMenu->SetPosition(sf::Vector2f(200.0f, 150.0f));
    //settingsMenu->SetPosition(sf::Vector2f((gameWidth / 1.5f), (gameHeight / 2.0f)));

  }
  setLoaded(true);
}
void MenuScene::UnLoad() { Scene::UnLoad(); }
void MenuScene::Update(const double& dt) {
  // cout << "Menu Update "<<dt<<"\n";
     if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
         Engine::GetWindow().setSize(Vector2u(1280,720));
         Engine::ChangeScene(&game);
     }
     if (sf::Keyboard::isKeyPressed(Keyboard::Num0)) {
         Engine::GetWindow().setSize(Vector2u(1280, 720));

     }

  Scene::Update(dt);
}
