#include "scene_dead.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void DeadScene::Load() {
  cout << "Game over screen Load \n";
  {
    auto txt = makeEntity();
    // Text on screen
    auto deadText = txt->addComponent<TextComponent>("You have joined the horde!");
    deadText->SetPosition(Vector2f(200.0f, 100.0f));
    auto backToMenu = txt->addComponent<TextComponent>("Press P to go back to menu.");
    backToMenu->SetPosition(Vector2f(200.0f, 150.0f));
  }
  setLoaded(true);
}
void DeadScene::UnLoad() { Scene::UnLoad(); }
void DeadScene::Update(const double& dt) {
     // Change resolution based on user input
    if (sf::Keyboard::isKeyPressed(Keyboard::P)) {
        Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y)));
        Engine::ChangeScene(&menu);
    }
    

  Scene::Update(dt);
}
