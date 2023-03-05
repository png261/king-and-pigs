#include "PlayState.hpp"
#include "Box.hpp"
#include "Camera.hpp"
#include "DoorObject.hpp"
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
    Camera::Instance()->setZoom(1.5);

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
    pGameObjectFactory->registerType("Door", new Creator<DoorObject>);

    pTextureManager->load("assets/Player/Idle.png", "player idle");
    pTextureManager->load("assets/Player/Run.png", "player run");
    pTextureManager->load("assets/Player/Jump.png", "player jump");
    pTextureManager->load("assets/Player/Attack.png", "player attack");
    pTextureManager->load("assets/Player/Dead.png", "player dead");
    pTextureManager->load("assets/Player/Fall.png", "player fall");
    pTextureManager->load("assets/Player/Ground.png", "player ground");
    pTextureManager->load("assets/Player/Hit.png", "player hit");
    pTextureManager->load("assets/Player/Door In.png", "player door in");
    pTextureManager->load("assets/Player/Door Out.png", "player door out");

    pTextureManager->load("assets/Enemy/Pig/Idle.png", "pig idle");
    pTextureManager->load("assets/Enemy/Pig/Run.png", "pig run");
    pTextureManager->load("assets/Enemy/Pig/Jump.png", "pig jump");
    pTextureManager->load("assets/Enemy/Pig/Attack.png", "pig attack");
    pTextureManager->load("assets/Enemy/Pig/Dead.png", "pig dead");
    pTextureManager->load("assets/Enemy/Pig/Fall.png", "pig fall");
    pTextureManager->load("assets/Enemy/Pig/Ground.png", "pig ground");
    pTextureManager->load("assets/Enemy/Pig/Hit.png", "pig hit");

    pTextureManager->load("assets/Item/Big Heart Idle.png", "heart idle");
    pTextureManager->load("assets/Item/Big Heart Hit.png", "heart hit");
    pTextureManager->load("assets/Item/Big Diamond Idle.png", "diamond idle");
    pTextureManager->load("assets/Item/Big Diamond Hit.png", "diamond hit");

    pTextureManager->load("assets/Item/Door/idle.png", "door idle");
    pTextureManager->load("assets/Item/Door/open.png", "door open");
    pTextureManager->load("assets/Item/Door/close.png", "door close");

    pTextureManager->load("assets/Item/Box/Idle.png", "box idle");
    pTextureManager->load("assets/Item/Box/Hit.png", "box hit");

    pTextureManager->load("assets/UI/Health Bar/Health Bar.png", "health bar");
    pTextureManager->load("assets/UI/Health Bar/Heart.png", "health heart");

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
