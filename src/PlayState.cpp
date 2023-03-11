#include "PlayState.hpp"
#include "Box.hpp"
#include "CONSTANT.hpp"
#include "Camera.hpp"
#include "Door.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "Heart.hpp"
#include "InputHandler.hpp"
#include "LevelParser.hpp"
#include "LoaderParams.hpp"
#include "Pig.hpp"
#include "Player.hpp"


const std::string PlayState::s_stateID = "PLAY";

bool PlayState::onEnter()
{
    if (this->load() == false) {
        return false;
    };


    Camera::Instance()->setTarget(Game::Instance()->getPlayer());
    Camera::Instance()->setZoom(2);

    m_loadingComplete = true;
    return true;
}

bool PlayState::load()
{
    TextureManager* const pTextureManager = TextureManager::Instance();
    GameObjectFactory* const pGameObjectFactory = GameObjectFactory::Instance();

    pGameObjectFactory->registerType("Player", new Creator<Player>);
    pGameObjectFactory->registerType("Pig", new Creator<Pig>);
    pGameObjectFactory->registerType("Box", new Creator<Box>);
    pGameObjectFactory->registerType("Heart", new Creator<Heart>);
    pGameObjectFactory->registerType("Door", new Creator<Door>);

    pTextureManager->load(ASSETS_DIR + "Player/Idle.png", "player idle");
    pTextureManager->load(ASSETS_DIR + "Player/Run.png", "player run");
    pTextureManager->load(ASSETS_DIR + "Player/Jump.png", "player jump");
    pTextureManager->load(ASSETS_DIR + "Player/Attack.png", "player attack");
    pTextureManager->load(ASSETS_DIR + "Player/Dead.png", "player dead");
    pTextureManager->load(ASSETS_DIR + "Player/Fall.png", "player fall");
    pTextureManager->load(ASSETS_DIR + "Player/Ground.png", "player ground");
    pTextureManager->load(ASSETS_DIR + "Player/Hit.png", "player hit");
    pTextureManager->load(ASSETS_DIR + "Player/Door In.png", "player door in");
    pTextureManager->load(ASSETS_DIR + "Player/Door Out.png", "player door out");

    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Idle.png", "pig idle");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Run.png", "pig run");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Jump.png", "pig jump");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Attack.png", "pig attack");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Dead.png", "pig dead");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Fall.png", "pig fall");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Ground.png", "pig ground");
    pTextureManager->load(ASSETS_DIR + "Enemy/Pig/Hit.png", "pig hit");

    pTextureManager->load(ASSETS_DIR + "Item/Big Heart Idle.png", "heart idle");
    pTextureManager->load(ASSETS_DIR + "Item/Big Heart Hit.png", "heart hit");
    pTextureManager->load(ASSETS_DIR + "Item/Big Diamond Idle.png", "diamond idle");
    pTextureManager->load(ASSETS_DIR + "Item/Big Diamond Hit.png", "diamond hit");

    pTextureManager->load(ASSETS_DIR + "Item/Door/idle.png", "door idle");
    pTextureManager->load(ASSETS_DIR + "Item/Door/open.png", "door open");
    pTextureManager->load(ASSETS_DIR + "Item/Door/close.png", "door close");

    pTextureManager->load(ASSETS_DIR + "Item/Box/Idle.png", "box idle");
    pTextureManager->load(ASSETS_DIR + "Item/Box/Hit.png", "box hit");

    pTextureManager->load(ASSETS_DIR + "UI/Health Bar/Health Bar.png", "health bar");
    pTextureManager->load(ASSETS_DIR + "UI/Health Bar/Heart.png", "health heart");

    LevelParser levelParser;
    pLevel = levelParser.parseLevel(
        Game::Instance()->getLevel(Game::Instance()->getCurrentLevel()).c_str());
    if (pLevel == nullptr) {
        return false;
    }

    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    InputHandler::Instance()->reset();

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

    if (pLevel != nullptr) {
        pLevel->update();
    }
    Camera::Instance()->update();
}

void PlayState::render()
{
    if (!m_loadingComplete || m_exiting) {
        return;
    }

    if (pLevel != nullptr) {
        pLevel->render();
    }
}
