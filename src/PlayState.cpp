#include "PlayState.hpp"
#include "Bomb.hpp"
#include "Box.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Camera.hpp"
#include "Candle.hpp"
#include "DoorIn.hpp"
#include "DoorOut.hpp"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GameStateMachine.hpp"
#include "Heart.hpp"
#include "InputHandler.hpp"
#include "KingPig.hpp"
#include "LevelParser.hpp"
#include "Log.hpp"
#include "PauseState.hpp"
#include "Pig.hpp"
#include "PigWithBomb.hpp"
#include "PigWithBox.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

const std::string PlayState::s_stateID = "PLAY";

PlayState::~PlayState() {}

PlayState::PlayState()
    : GameState()
    , m_bDebug(false)
{}

bool PlayState::onEnter()
{
    if (this->load() == false) {
        return false;
    };
    return true;
}

void PlayState::s_mute()
{
    SoundManager::Instance()->muteMusic();
}

bool PlayState::load()
{
    m_bLoaded = false;
    GameObjectFactory* const factory = GameObjectFactory::Instance();
    TextureManager* const texture = TextureManager::Instance();
    SoundManager* const sound = SoundManager::Instance();

    factory->registerType("Player", new Creator<Player>);
    factory->registerType("Pig", new Creator<Pig>);
    factory->registerType("KingPig", new Creator<KingPig>);
    factory->registerType("PigWithBomb", new Creator<PigWithBomb>);
    factory->registerType("PigWithBox", new Creator<PigWithBox>);
    factory->registerType("Bomb", new Creator<Bomb>);
    factory->registerType("Box", new Creator<Box>);
    factory->registerType("Heart", new Creator<Heart>);
    factory->registerType("DoorOut", new Creator<DoorOut>);
    factory->registerType("DoorIn", new Creator<DoorIn>);
    factory->registerType("Candle", new Creator<Candle>);

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

    texture->load(ASSETS_DIR + "Enemy/KingPig/Idle.png", "kingPig idle");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Run.png", "kingPig run");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Jump.png", "kingPig jump");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Attack.png", "kingPig attack");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Dead.png", "kingPig dead");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Fall.png", "kingPig fall");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Ground.png", "kingPig ground");
    texture->load(ASSETS_DIR + "Enemy/KingPig/Hit.png", "kingPig hit");

    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Idle.png", "pigWithBomb idle");
    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Run.png", "pigWithBomb run");
    texture->load(ASSETS_DIR + "Enemy/PigWithBomb/Throwing.png", "pigWithBomb throwing");

    texture->load(ASSETS_DIR + "Enemy/PigWithBox/Idle.png", "pigWithBox idle");
    texture->load(ASSETS_DIR + "Enemy/PigWithBox/Run.png", "pigWithBox run");
    texture->load(ASSETS_DIR + "Enemy/PigWithBox/Throwing.png", "pigWithBox throwing");

    texture->load(ASSETS_DIR + "Item/Heart/Idle.png", "heart idle");
    texture->load(ASSETS_DIR + "Item/Heart/Hit.png", "heart hit");

    texture->load(ASSETS_DIR + "Item/Diamond/Idle.png", "diamond idle");
    texture->load(ASSETS_DIR + "Item/Diamond/Hit.png", "diamond hit");

    texture->load(ASSETS_DIR + "Item/Door/Idle.png", "door idle");
    texture->load(ASSETS_DIR + "Item/Door/Open.png", "door open");
    texture->load(ASSETS_DIR + "Item/Door/Close.png", "door close");

    texture->load(ASSETS_DIR + "Item/Candle/Idle.png", "candle idle");

    texture->load(ASSETS_DIR + "Item/Box/Idle.png", "box idle");
    texture->load(ASSETS_DIR + "Item/Box/Hit.png", "box hit");

    texture->load(ASSETS_DIR + "Item/Bomb/On.png", "bomb on");
    texture->load(ASSETS_DIR + "Item/Bomb/Off.png", "bomb off");
    texture->load(ASSETS_DIR + "Item/Bomb/Explode.png", "bomb explode");

    texture->load(ASSETS_DIR + "UI/Health Bar/Health Bar.png", "health bar");
    texture->load(ASSETS_DIR + "UI/Health Bar/Heart.png", "health heart");

    texture->load(ASSETS_DIR + "UI/Button/normal.png", "button normal");
    texture->load(ASSETS_DIR + "UI/Button/hovered.png", "button hovered");
    texture->load(ASSETS_DIR + "UI/Button/pressed.png", "button pressed");

    sound->loadMusic(ASSETS_DIR + "sounds/background.ogg", "background");
    sound->loadSFX(ASSETS_DIR + "sounds/jump.wav", "jump");
    sound->playMusic("background");


    if (this->loadLevel() == false) {
        return false;
    }


    m_bLoaded = true;

    return true;
}

bool PlayState::loadLevel()
{
    this->onExit();
    LevelParser levelParser;
    m_pLevel = std::unique_ptr<Level>(levelParser.parseLevel(
        Game::Instance()->loadLevel(Game::Instance()->getCurrentLevel()).c_str()));
    Game::Instance()->setLevel(m_pLevel.get());

    if (m_pLevel == nullptr) {
        return false;
    }
    Camera::Instance()->setTarget(m_pLevel->getPlayer());
    Camera::Instance()->setZoom(2);
    this->resume();

    return true;
}

bool PlayState::onExit()
{
    m_bPaused = true;
    InputHandler::Instance()->reset();
    PhysicWorld::Instance()->clean();

    return true;
}

void PlayState::resume()
{
    m_bPaused = false;
}

void PlayState::update()
{
    if (!m_bLoaded || m_bPaused || m_pLevel == nullptr) {
        return;
    }
    if (InputHandler::Instance()->isKeyDown(KEY_ESCAPE)) {
        GameStateMachine::Instance()->pushState(new PauseState());
    }

    PhysicWorld::Instance()->update();
    m_pLevel->update();
    Camera::Instance()->update();
}

void PlayState::render()
{
    if (!m_bLoaded || m_bPaused || m_pLevel == nullptr) {
        return;
    }

    m_pLevel->render();

    if (InputHandler::Instance()->isKeyDown(KEY_Q)) {
        m_bDebug = !m_bDebug;
    };

    if (m_bDebug) {
        PhysicWorld::Instance()->debugDraw();
    }
}

std::string PlayState::getStateID() const
{
    return s_stateID;
}
