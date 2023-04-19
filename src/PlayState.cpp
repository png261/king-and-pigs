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

    texture.load(IMAGE_DIRECTORY + "player/idle.png", "player idle");
    texture.load(IMAGE_DIRECTORY + "player/run.png", "player run");
    texture.load(IMAGE_DIRECTORY + "player/jump.png", "player jump");
    texture.load(IMAGE_DIRECTORY + "player/attack.png", "player attack");
    texture.load(IMAGE_DIRECTORY + "player/dead.png", "player dead");
    texture.load(IMAGE_DIRECTORY + "player/fall.png", "player fall");
    texture.load(IMAGE_DIRECTORY + "player/ground.png", "player ground");
    texture.load(IMAGE_DIRECTORY + "player/hit.png", "player hit");
    texture.load(IMAGE_DIRECTORY + "player/entering_door.png", "player entering door");
    texture.load(IMAGE_DIRECTORY + "player/leaving_door.png", "player leaving door");

    texture.load(IMAGE_DIRECTORY + "enemy/pig/idle.png", "pig idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/run.png", "pig run");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/jump.png", "pig jump");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/attack.png", "pig attack");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/dead.png", "pig dead");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/fall.png", "pig fall");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/ground.png", "pig ground");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/hit.png", "pig hit");

    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/idle.png", "kingPig idle");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/run.png", "kingPig run");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/jump.png", "kingPig jump");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/attack.png", "kingPig attack");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/dead.png", "kingPig dead");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/fall.png", "kingPig fall");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/ground.png", "kingPig ground");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/hit.png", "kingPig hit");

    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/idle.png", "pigWithBomb idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/run.png", "pigWithBomb run");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/throwing.png", "pigWithBomb throwing");

    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/idle.png", "pigWithBox idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/run.png", "pigWithBox run");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/throwing.png", "pigWithBox throwing");

    texture.load(IMAGE_DIRECTORY + "item/heart/idle.png", "heart idle");
    texture.load(IMAGE_DIRECTORY + "item/heart/hit.png", "heart hit");
    texture.load(IMAGE_DIRECTORY + "item/diamond/idle.png", "diamond idle");
    texture.load(IMAGE_DIRECTORY + "item/diamond/hit.png", "diamond hit");

    texture.load(IMAGE_DIRECTORY + "item/diamond/idle.png", "diamond idle");
    texture.load(IMAGE_DIRECTORY + "item/diamond/hit.png", "diamond hit");

    texture.load(IMAGE_DIRECTORY + "item/door/idle.png", "door idle");
    texture.load(IMAGE_DIRECTORY + "item/door/open.png", "door open");
    texture.load(IMAGE_DIRECTORY + "item/door/close.png", "door close");

    texture.load(IMAGE_DIRECTORY + "item/candle/idle.png", "candle idle");

    texture.load(IMAGE_DIRECTORY + "item/box/idle.png", "box idle");
    texture.load(IMAGE_DIRECTORY + "item/box/hit.png", "box hit");

    texture.load(IMAGE_DIRECTORY + "item/bomb/on.png", "bomb on");
    texture.load(IMAGE_DIRECTORY + "item/bomb/off.png", "bomb off");
    texture.load(IMAGE_DIRECTORY + "item/bomb/explode.png", "bomb explode");

    texture.load(IMAGE_DIRECTORY + "ui/healthbar/healthbar.png", "health bar");
    texture.load(IMAGE_DIRECTORY + "ui/healthbar/heart.png", "health heart");

    sound.loadSFX(SOUND_DIRECTORY + "player/attack.wav", "player attack");
    sound.loadSFX(SOUND_DIRECTORY + "player/dying.wav", "player dying");
    sound.loadSFX(SOUND_DIRECTORY + "player/jump.wav", "player jump");

    sound.loadSFX(SOUND_DIRECTORY + "pig/attack.wav", "pig attack");
    sound.loadSFX(SOUND_DIRECTORY + "pig/dying.wav", "pig dying");

    sound.loadSFX(SOUND_DIRECTORY + "door/close.wav", "door close");
    sound.loadSFX(SOUND_DIRECTORY + "door/open.wav", "door open");

    sound.loadSFX(SOUND_DIRECTORY + "bomb/on.wav", "bomb on");
    sound.loadSFX(SOUND_DIRECTORY + "bomb/explode.wav", "bomb explode");

    sound.loadSFX(SOUND_DIRECTORY + "box/break.wav", "box broken");

    sound.loadSFX(SOUND_DIRECTORY + "heart/bonus.wav", "heart bonus");

    sound.loadMusic(SOUND_DIRECTORY + "playstate/background.wav", "playstate background");

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
    pause();
    PhysicWorld::Instance().clean();
    InputHandler::Instance().reset();

    return true;
}

void PlayState::update()
{
    if (!isLoaded() || isPaused() || m_pLevel == nullptr) {
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
    if (!isLoaded() || isPaused() || m_pLevel == nullptr) {
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
