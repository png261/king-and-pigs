#include "PlayState.hpp"
#include "Box.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "Heart.hpp"
#include "InputHandler.hpp"
#include "LevelParser.hpp"
#include "LoaderParams.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "Pig.hpp"
#include "Player.hpp"


const std::string PlayState::s_stateID = "PLAY";

bool PlayState::onEnter()
{
    Log::log("enter playstate");

    GameObjectFactory::Instance()->registerType("Player", new Creator<Player>);
    GameObjectFactory::Instance()->registerType("Pig", new Creator<Pig>);
    GameObjectFactory::Instance()->registerType("Box", new Creator<Box>);
    GameObjectFactory::Instance()->registerType("Heart", new Creator<Heart>);

    LevelParser levelParser;
    pLevel = levelParser.parseLevel(
        TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());
    if (pLevel == NULL) {
        return false;
    }

    SDL_Renderer* pRenderer = Game::Instance()->getRenderer();

    TextureManager::Instance()
        ->load("assets/01-King Human/Idle (78x58).png", "player idle", pRenderer, 11);
    TextureManager::Instance()
        ->load("assets/01-King Human/Run (78x58).png", "player run", pRenderer, 8);
    TextureManager::Instance()
        ->load("assets/01-King Human/Jump (78x58).png", "player jump", pRenderer, 1);
    TextureManager::Instance()
        ->load("assets/01-King Human/Attack (78x58).png", "player attack", pRenderer, 3);
    TextureManager::Instance()
        ->load("assets/01-King Human/Dead (78x58).png", "player dead", pRenderer, 4);
    TextureManager::Instance()
        ->load("assets/01-King Human/Fall (78x58).png", "player fall", pRenderer, 1);
    TextureManager::Instance()
        ->load("assets/01-King Human/Ground (78x58).png", "player ground", pRenderer, 1);
    TextureManager::Instance()
        ->load("assets/01-King Human/Hit (78x58).png", "player hit", pRenderer, 2);
    TextureManager::Instance()
        ->load("assets/01-King Human/Door In (78x58).png", "player doorIn", pRenderer, 8);
    TextureManager::Instance()
        ->load("assets/01-King Human/Door In (78x58).png", "player doorIn", pRenderer, 8);
    TextureManager::Instance()
        ->load("assets/01-King Human/Door Out (78x58).png", "player doorOut", pRenderer, 8);

    TextureManager::Instance()->load("assets/03-Pig/Idle (34x28).png", "pig idle", pRenderer, 11);
    TextureManager::Instance()->load("assets/03-Pig/Run (34x28).png", "pig run", pRenderer, 6);
    TextureManager::Instance()->load("assets/03-Pig/Jump (34x28).png", "pig jump", pRenderer, 1);
    TextureManager::Instance()
        ->load("assets/03-Pig/Attack (34x28).png", "pig attack", pRenderer, 3);
    TextureManager::Instance()->load("assets/03-Pig/Dead (34x28).png", "pig dead", pRenderer, 4);
    TextureManager::Instance()->load("assets/03-Pig/Fall (34x28).png", "pig fall", pRenderer, 1);
    TextureManager::Instance()
        ->load("assets/03-Pig/Ground (34x28).png", "pig ground", pRenderer, 1);
    TextureManager::Instance()->load("assets/03-Pig/Hit (34x28).png", "pig hit", pRenderer, 2);

    TextureManager::Instance()->load(
        "assets/7-Objects/11-Health Bar/Health Bar.png",
        "health bar",
        pRenderer);

    TextureManager::Instance()->load(
        "assets/7-Objects/11-Health Bar/Heart.png",
        "health heart",
        pRenderer);

    TextureManager::Instance()->load("assets/08-Box/Idle.png", "box idle", pRenderer, 0);

    TextureManager::Instance()
        ->load("assets/12-Live and Coins/Big Heart Idle (18x14).png", "heart idle", pRenderer, 7);
    TextureManager::Instance()
        ->load("assets/12-Live and Coins/Big Heart Hit (18x14).png", "heart hit", pRenderer, 2);

    m_loadingComplete = true;
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    TheInputHandler::Instance()->reset();

    Log::log("exit playstate");

    return true;
}

void PlayState::resume()
{
    m_exiting = false;
}

void PlayState::update()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }

    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        GameStateMachine::Instance()->pushState(new PauseState);
    }

    if (pLevel != NULL) {
        pLevel->update();
    }
    TheCamera::Instance()->update();
}

void PlayState::render()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }

    if (pLevel != NULL) {
        pLevel->render();
    }

    TheTextureManager::Instance()
        ->draw("health bar", 10, 10, 154, 62, Game::Instance()->getRenderer());

    for (int i = 0; i < Game::Instance()->getPlayer()->getLives(); i++) {
        TheTextureManager::Instance()
            ->draw("health heart", 50 + 25 * i, 33, 22, 19, Game::Instance()->getRenderer());
    }
}
