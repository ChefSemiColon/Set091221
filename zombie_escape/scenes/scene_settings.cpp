#include "scene_settings.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void SettingsScene::Load() {
  cout << "Settings Load \n";
  {
    auto txt = makeEntity();
    // Can't use dynamic position for menu since the game size is bigger than the window, so in smaller screen menu might get hidden
    auto bigRes = txt->addComponent<TextComponent>("1 - Resolution - 2560x1440");
    bigRes->SetPosition(Vector2f(200.0f, 100.0f));
    auto smallRes = txt->addComponent<TextComponent>("2 - Resolution - 1280x720");
    smallRes->SetPosition(Vector2f(200.0f, 150.0f));
    auto mediumRes = txt->addComponent<TextComponent>("3 - Resolution - 1920x1080");
    mediumRes->SetPosition(Vector2f(200.0f, 200.0f));
    auto fullscreen = txt->addComponent<TextComponent>("4 - Fullscreen");
    fullscreen->SetPosition(Vector2f(200.0f, 250.0f));
    auto backToMenu = txt->addComponent<TextComponent>("5 - Back to Menu");
    backToMenu->SetPosition(Vector2f(200.0f, 300.0f));

  }
  setLoaded(true);
}
void SettingsScene::UnLoad() { Scene::UnLoad(); }
void SettingsScene::Update(const double& dt) {
     // Change resolution based on user input
     if (Keyboard::isKeyPressed(Keyboard::Num1)) {
         Engine::GetWindow().setSize(Vector2u(2560,1440));
     }
     if (Keyboard::isKeyPressed(Keyboard::Num2)) {
         Engine::GetWindow().setSize(Vector2u(1280, 720));
     }
     if (Keyboard::isKeyPressed(Keyboard::Num3)) {
         Engine::GetWindow().setSize(Vector2u(1920, 1080));
     }
     if (Keyboard::isKeyPressed(Keyboard::Num5)) {
         Engine::ChangeScene(&menu);
     }

  Scene::Update(dt);
}
