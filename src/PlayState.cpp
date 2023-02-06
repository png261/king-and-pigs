#include "PlayState.h"
#include "Player.h"
#include "LoaderParams.h"

#include <iostream>

const std::string PlayState::s_stateID = "PLAY";

void PlayState::enter() {
    std::cout << "enter playstate" << std::endl;

    Player* player = new Player();
    player->load(new LoaderParams(100, 100, 78, 58, "player idle", 10, 0, 100));
    m_gameObjects.push_back(dynamic_cast<GameObject*>(player));
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
