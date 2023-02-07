#include "PlayState.h"
#include "Enemy.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "LoaderParams.h"
#include "Pig.h"
#include "Player.h"

#include <iostream>

const std::string PlayState::s_stateID = "PLAY";

void PlayState::enter() {
    std::cout << "enter playstate" << std::endl;
    TheGame::Instance()->setPlayerLives(3);

    LevelParser levelParser;
    pLevel = levelParser.parseLevel(
        TheGame::Instance()
            ->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1]
            .c_str());
    if (pLevel != NULL) {
        m_loadingComplete = true;
    }
}

void PlayState::exit() {
    m_exiting = true;
    TheInputHandler::Instance()->reset();

    std::cout << "exit playstate" << std::endl;
}

void PlayState::resume() { std::cout << "exit playstate" << std::endl; }

void PlayState::update() {
    if (pLevel != 0) {
        pLevel->update();
    }
}

void PlayState::render() {
    if (pLevel != 0) {
        pLevel->render();
    }
    TheTextureManager::Instance()->draw("health bar", 10, 10, 154, 62,
                                        Game::Instance()->getRenderer());
    for (int i = 0; i < Game::Instance()->getPlayerLives(); i++) {
        TheTextureManager::Instance()->draw("health heart", 50 + 25 * i, 33, 22, 19,
                                            Game::Instance()->getRenderer());
    }
}
