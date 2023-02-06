#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "Pig.h"
#include "LoaderParams.h"

#include <iostream>

const std::string PlayState::s_stateID = "PLAY";

void PlayState::enter() {
    std::cout << "enter playstate" << std::endl;

    Player* player = new Player();
    player->load(new LoaderParams(100, 100, 78, 58, "player idle", 11, 0, 100));
    Pig* pig = new Pig();
    pig->load(new LoaderParams(300, 100, 34, 28, "enemy_pig idle", 11, 0, 100));
    m_gameObjects.push_back(dynamic_cast<GameObject*>(player));
    m_gameObjects.push_back(dynamic_cast<GameObject*>(pig));
}

void PlayState::exit() {
    std::cout << "exit playstate" << std::endl;
}

void PlayState::resume() {
    std::cout << "exit playstate" << std::endl;
}

void PlayState::update() {
    for(auto &obj : m_gameObjects) {
        obj->update();
    }
}

void PlayState::render() {
    for(auto &obj : m_gameObjects) {
        obj->draw();
    }
}
