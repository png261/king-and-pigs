#include "PlayState.hpp"
#include "Bomb.hpp"
#include "Box.hpp"
#include "CONSTANT.hpp"
#include "Camera.hpp"
#include "Decor.hpp"
#include "DoorIn.hpp"
#include "DoorOut.hpp"
#include "Enemy.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "Heart.hpp"
#include "InputHandler.hpp"
#include "LevelParser.hpp"
#include "Pig.hpp"
#include "PigWithBomb.hpp"
#include "Player.hpp"

const std::string PlayState::s_stateID = "PLAY";

PlayState::~PlayState() {}

bool PlayState::onEnter()
{
    if (this->load() == false) {
        return false;
    };

    m_loadingComplete = true;
    return true;
}


bool PlayState::load()
{
    TextureManager* const texture = TextureManager::Instance();
    GameObjectFactory* const factory = GameObjectFactory::Instance();

    factory->registerType("Player", new Creator<Player>);
    factory->registerType("Pig", new Creator<Pig>);
    factory->registerType("Box", new Creator<Box>);
    factory->registerType("Heart", new Creator<Heart>);
    factory->registerType("DoorOut", new Creator<DoorOut>);
    factory->registerType("DoorIn", new Creator<DoorIn>);
    factory->registerType("Bomb", new Creator<Bomb>);
    factory->registerType("PigWithBomb", new Creator<PigWithBomb>);
    factory->registerType("Decor", new Creator<Decor>);

    texture->load(ASSETS_DIR + "Player/Idle.png", "player idle");
    texture->load(ASSETS_DIR + "Player/Run.png", "player run");
    texture->load(ASSETS_DIR + "Player/Jump.png", "player jump");
    texture->load(ASSETS_DIR + "Player/Attack.png", "player attack");
    texture->load(ASSETS_DIR + "Player/Dead.png", "player dead");
    texture->load(ASSETS_DIR + "Player/Fall.png", "player fall");
    texture->load(ASSETS_DIR + "Player/Ground.png", "player ground");
    texture->load(ASSETS_DIR + "Player/Hit.png", "player hit");
    texture->load(ASSETS_DIR + "Player/Door In.png", "player door in");
    texture->load(ASSETS_DIR + "Player/Door Out.png", "player door out");

    texture->load(ASSETS_DIR + "Enemy/Pig/Idle.png", "pig idle");
    texture->load(ASSETS_DIR + "Enemy/Pig/Run.png", "pig run");
    texture->load(ASSETS_DIR + "Enemy/Pig/Jump.png", "pig jump");
    texture->load(ASSETS_DIR + "Enemy/Pig/Attack.png", "pig attack");
    texture->load(ASSETS_DIR + "Enemy/Pig/Dead.png", "pig dead");
    texture->load(ASSETS_DIR + "Enemy/Pig/Fall.png", "pig fall");
    texture->load(ASSETS_DIR + "Enemy/Pig/Ground.png", "pig ground");
    texture->load(ASSETS_DIR + "Enemy/Pig/Hit.png", "pig hit");

    texture->load(ASSETS_DIR + "Item/Big Heart Idle.png", "heart idle");
    texture->load(ASSETS_DIR + "Item/Big Heart Hit.png", "heart hit");
    texture->load(ASSETS_DIR + "Item/Big Diamond Idle.png", "diamond idle");
    texture->load(ASSETS_DIR + "Item/Big Diamond Hit.png", "diamond hit");

    texture->load(ASSETS_DIR + "Item/Door/idle.png", "door idle");
    texture->load(ASSETS_DIR + "Item/Door/open.png", "door open");
    texture->load(ASSETS_DIR + "Item/Door/close.png", "door close");

    texture->load(ASSETS_DIR + "Item/Candle/Idle.png", "candle idle");

    texture->load(ASSETS_DIR + "Item/Box/Idle.png", "box idle");
    texture->load(ASSETS_DIR + "Item/Box/Hit.png", "box hit");

    texture->load(ASSETS_DIR + "Item/Bomb/On.png", "bomb on");
    texture->load(ASSETS_DIR + "Item/Bomb/Off.png", "bomb off");
    texture->load(ASSETS_DIR + "Item/Bomb/Explode.png", "bomb explode");

    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Idle.png", "pigWithBomb idle");
    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Run.png", "pigWithBomb run");
    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Throwing.png", "pigWithBomb throwing");

    texture->load(ASSETS_DIR + "UI/Health Bar/Health Bar.png", "health bar");
    texture->load(ASSETS_DIR + "UI/Health Bar/Heart.png", "health heart");

    if (this->loadLevel() == false) {
        return false;
    }

    Camera::Instance()->setTarget(m_pLevel->getPlayer());
    Camera::Instance()->setZoom(2);

    return true;
}

bool PlayState::loadLevel()
{
    LevelParser levelParser;
    m_pLevel = std::unique_ptr<Level>(levelParser.parseLevel(
        Game::Instance()->getLevel(Game::Instance()->getCurrentLevel()).c_str()));

    if (m_pLevel == nullptr) {
        return false;
    }
    return true;
}

bool PlayState::onExit()
{
    m_exiting = true;
    InputHandler::Instance()->reset();
    PhysicWorld::Instance()->clean();

    return true;
}

void PlayState::resume()
{
    m_exiting = false;
}

void PlayState::update()
{
    if (!m_loadingComplete || m_exiting || m_pLevel == nullptr) {
        return;
    }
    if (InputHandler::Instance()->isKeyDown(KEY_Z)) {
        Game::Instance()->nextLevel();
    }

    m_pLevel->update();
    Camera::Instance()->update();
}

void PlayState::render()
{
    if (!m_loadingComplete || m_exiting || m_pLevel == nullptr) {
        return;
    }

    m_pLevel->render();
}

std::string PlayState::getStateID() const
{
    return s_stateID;
}
