#include "scene_dead.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

// Get a random score from 3 values
int randomScore(int killCount, int one, int two, int three)
{
    int randomScore = 0;
    if (killCount == 0){}
    else
    {
        for (int i = 0; i < killCount; i++)
        {
            int randomNumber = 0;
            int randomiser = rand() % 3;
            switch (randomiser) {
            case 0:
                randomNumber = one;
                break;
            case 1:
                randomNumber = two;
                break;
            case 2:
                randomNumber = three;
                break;
            }
            randomScore += randomNumber;
        }
    }
    return randomScore;
}

void DeadScene::Load() {
  cout << "Game over screen Load \n";
  {
    auto txt = makeEntity();

    string score = "Score: " + to_string(randomScore(enemiesKilledTotal, 50, 75, 100)) + "    ||    Numbers of enemies killed: " + to_string(enemiesKilledTotal);
    // Reset the enemies killed counter
    enemiesKilledTotal = 0;
    // Text on screen
    auto deadText = txt->addComponent<TextComponent>("You have joined the horde!");
    deadText->SetPosition(Vector2f(Engine::GetWindow().getSize().x/2-300, Engine::GetWindow().getSize().y/2-200));
    auto scoreText = txt->addComponent<TextComponent>(score);
    scoreText->SetPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 500, Engine::GetWindow().getSize().y / 2 - 100));
    auto backToMenu = txt->addComponent<TextComponent>("Press P to go back to menu.");
    backToMenu->SetPosition(Vector2f(Engine::GetWindow().getSize().x/2-300, Engine::GetWindow().getSize().y/2));
  }
  setLoaded(true);
}
void DeadScene::UnLoad() { Scene::UnLoad(); }
void DeadScene::Update(const double& dt) {
     // Go back to menu
    if (sf::Keyboard::isKeyPressed(Keyboard::P)) {
        Engine::GetWindow().setView(sf::View(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y)));
        Engine::ChangeScene(&menu);
    }
  Scene::Update(dt);
}
