#include "PlayState.hpp"

#include "Bomb.hpp"
#include "Box.hpp"
#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Camera.hpp"
#include "Candle.hpp"
#include "Diamond.hpp"
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

PlayState::PlayState()
    : GameState()
{}

bool PlayState::enter()
{
    m_bLoaded = false;
    GameObjectFactory& factory = GameObjectFactory::Instance();
    TextureManager& texture = TextureManager::Instance();
    SoundManager& sound = SoundManager::Instance();

    factory.registerType("Player", std::make_unique<PlayerCreator>());
    factory.registerType("Pig", std::make_unique<PigCreator>());
    factory.registerType("KingPig", std::make_unique<KingPigCreator>());
    factory.registerType("PigWithBomb", std::make_unique<PigWithBombCreator>());
    factory.registerType("PigWithBox", std::make_unique<PigWithBoxCreator>());
    factory.registerType("Bomb", std::make_unique<BombCreator>());
    factory.registerType("Box", std::make_unique<BoxCreator>());
    factory.registerType("Heart", std::make_unique<HeartCreator>());
    factory.registerType("Diamond", std::make_unique<DiamondCreator>());
    factory.registerType("DoorOut", std::make_unique<DoorOutCreator>());
    factory.registerType("DoorIn", std::make_unique<DoorInCreator>());
    factory.registerType("Candle", std::make_unique<CandleCreator>());

    texture.load(IMAGE_DIRECTORY + "Player/Idle.png", "player idle");
    texture.load(IMAGE_DIRECTORY + "Player/Run.png", "player run");
    texture.load(IMAGE_DIRECTORY + "Player/Jump.png", "player jump");
    texture.load(IMAGE_DIRECTORY + "Player/Attack.png", "player attack");
    texture.load(IMAGE_DIRECTORY + "Player/Dead.png", "player dead");
    texture.load(IMAGE_DIRECTORY + "Player/Fall.png", "player fall");
    texture.load(IMAGE_DIRECTORY + "Player/Ground.png", "player ground");
    texture.load(IMAGE_DIRECTORY + "Player/Hit.png", "player hit");
    texture.load(IMAGE_DIRECTORY + "Player/Door In.png", "player door in");
    texture.load(IMAGE_DIRECTORY + "Player/Door Out.png", "player door out");

    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Idle.png", "pig idle");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Run.png", "pig run");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Jump.png", "pig jump");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Attack.png", "pig attack");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Dead.png", "pig dead");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Fall.png", "pig fall");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Ground.png", "pig ground");
    texture.load(IMAGE_DIRECTORY + "Enemy/Pig/Hit.png", "pig hit");

    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Idle.png", "kingPig idle");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Run.png", "kingPig run");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Jump.png", "kingPig jump");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Attack.png", "kingPig attack");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Dead.png", "kingPig dead");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Fall.png", "kingPig fall");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Ground.png", "kingPig ground");
    texture.load(IMAGE_DIRECTORY + "Enemy/KingPig/Hit.png", "kingPig hit");

    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBomb/Idle.png", "pigWithBomb idle");
    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBomb/Run.png", "pigWithBomb run");
    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBomb/Throwing.png", "pigWithBomb throwing");

    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBox/Idle.png", "pigWithBox idle");
    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBox/Run.png", "pigWithBox run");
    texture.load(IMAGE_DIRECTORY + "Enemy/PigWithBox/Throwing.png", "pigWithBox throwing");

    texture.load(IMAGE_DIRECTORY + "Item/Heart/Idle.png", "heart idle");
    texture.load(IMAGE_DIRECTORY + "Item/Heart/Hit.png", "heart hit");
    texture.load(IMAGE_DIRECTORY + "Item/Diamond/Idle.png", "diamond idle");
    texture.load(IMAGE_DIRECTORY + "Item/Diamond/Hit.png", "diamond hit");

    texture.load(IMAGE_DIRECTORY + "Item/Diamond/Idle.png", "diamond idle");
    texture.load(IMAGE_DIRECTORY + "Item/Diamond/Hit.png", "diamond hit");

    texture.load(IMAGE_DIRECTORY + "Item/Door/Idle.png", "door idle");
    texture.load(IMAGE_DIRECTORY + "Item/Door/Open.png", "door open");
    texture.load(IMAGE_DIRECTORY + "Item/Door/Close.png", "door close");

    texture.load(IMAGE_DIRECTORY + "Item/Candle/Idle.png", "candle idle");

    texture.load(IMAGE_DIRECTORY + "Item/Box/Idle.png", "box idle");
    texture.load(IMAGE_DIRECTORY + "Item/Box/Hit.png", "box hit");

    texture.load(IMAGE_DIRECTORY + "Item/Bomb/On.png", "bomb on");
    texture.load(IMAGE_DIRECTORY + "Item/Bomb/Off.png", "bomb off");
    texture.load(IMAGE_DIRECTORY + "Item/Bomb/Explode.png", "bomb explode");

    texture.load(IMAGE_DIRECTORY + "UI/Health Bar/Health Bar.png", "health bar");
    texture.load(IMAGE_DIRECTORY + "UI/Health Bar/Heart.png", "health heart");

    texture.load(IMAGE_DIRECTORY + "UI/Button/normal.png", "button normal");
    texture.load(IMAGE_DIRECTORY + "UI/Button/hovered.png", "button hovered");
    texture.load(IMAGE_DIRECTORY + "UI/Button/pressed.png", "button pressed");

    sound.loadSFX(SOUND_DIRECTORY + "Player/attack.wav", "player attack");
    sound.loadSFX(SOUND_DIRECTORY + "Player/dying.wav", "player dying");
    sound.loadSFX(SOUND_DIRECTORY + "Player/jump.wav", "player jump");

    sound.loadSFX(SOUND_DIRECTORY + "Pig/attack.wav", "pig attack");
    sound.loadSFX(SOUND_DIRECTORY + "Pig/dying.wav", "pig dying");

    sound.loadSFX(SOUND_DIRECTORY + "Door/close.wav", "door close");
    sound.loadSFX(SOUND_DIRECTORY + "Door/open.wav", "door open");

    sound.loadSFX(SOUND_DIRECTORY + "Bomb/on.wav", "bomb on");
    sound.loadSFX(SOUND_DIRECTORY + "Bomb/explode.wav", "bomb explode");

    sound.loadSFX(SOUND_DIRECTORY + "Box/break.wav", "box broken");

    sound.loadSFX(SOUND_DIRECTORY + "Heart/bonus.wav", "heart bonus");

    sound.loadMusic(SOUND_DIRECTORY + "PlayState/background.wav", "playstate background");

    if (!loadLevel()) {
        return false;
    }

    /* sound.setVolume(0); */
    sound.playMusic("playstate background");
    m_bLoaded = true;

    return true;
}

bool PlayState::loadLevel()
{
    exit();

    LevelParser levelParser;
    m_pLevel = levelParser.parseLevel(
        Game::Instance().getLevelPath(Game::Instance().getLevelIndex()).c_str());

    if (m_pLevel == nullptr) {
        return false;
    }

    PhysicWorld::Instance().createContactListener();
    Game::Instance().setLevel(m_pLevel.get());
    Camera::Instance().setTarget(m_pLevel->getPlayer());
    Camera::Instance().setZoom(3);

    resume();
    return true;
}

bool PlayState::exit()
{
    m_bPaused = true;
    PhysicWorld::Instance().clean();
    InputHandler::Instance().reset();

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

    if (InputHandler::Instance().isKeyDown(KEY_ESCAPE)) {
        GameStateMachine::Instance().pushState(std::make_unique<PauseState>());
    }

    if (InputHandler::Instance().isKeyDown(KEY_Q)) {
        Game::Instance().toggleDebug();
    };

    PhysicWorld::Instance().update();
    m_pLevel->update();
    Camera::Instance().update();
}

void PlayState::render() const
{
    if (!m_bLoaded || m_bPaused || m_pLevel == nullptr) {
        return;
    }

    m_pLevel->render();

    if (Game::Instance().isDebug()) {
        PhysicWorld::Instance().debugDraw();
    }

    renderStatusBar();
}

void PlayState::renderStatusBar() const
{
    TextureManager::Instance().draw("health bar", {20, 10}, 154, 62);
    for (int i = 0; i < m_pLevel->getPlayer()->getHp(); i++) {
        TextureManager::Instance().draw("health heart", {60 + i * 25.0f, 30}, 22, 19);
    }

    Game::Instance().getWindow()->print(
        "level: " + std::to_string(Game::Instance().getLevelIndex() + 1),
        40,
        300,
        50,
        Color::WHITE);

    Game::Instance().getWindow()->print(
        "diamond: " + std::to_string(Game::Instance().getDiamond()),
        40,
        300 + 200,
        50,
        Color::WHITE);
}

std::string PlayState::getStateID() const
{
    return s_stateID;
}
