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

const std::string PlayState::kId_ = "PLAY";

PlayState::PlayState()
    : GameState()
{}

bool PlayState::enter()
{
    is_loaded_ = false;
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

    texture.load(IMAGE_DIRECTORY + "player/idle.png", "player_idle");
    texture.load(IMAGE_DIRECTORY + "player/run.png", "player_run");
    texture.load(IMAGE_DIRECTORY + "player/jump.png", "player_jump");
    texture.load(IMAGE_DIRECTORY + "player/attack.png", "player_attack");
    texture.load(IMAGE_DIRECTORY + "player/dead.png", "player_dead");
    texture.load(IMAGE_DIRECTORY + "player/fall.png", "player_fall");
    texture.load(IMAGE_DIRECTORY + "player/ground.png", "player_ground");
    texture.load(IMAGE_DIRECTORY + "player/hit.png", "player_hit");
    texture.load(IMAGE_DIRECTORY + "player/entering_door.png", "player_entering_door");
    texture.load(IMAGE_DIRECTORY + "player/leaving_door.png", "player_leaving_door");

    texture.load(IMAGE_DIRECTORY + "enemy/pig/idle.png", "pig_idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/run.png", "pig_run");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/jump.png", "pig_jump");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/attack.png", "pig_attack");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/dead.png", "pig_dead");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/fall.png", "pig_fall");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/ground.png", "pig_ground");
    texture.load(IMAGE_DIRECTORY + "enemy/pig/hit.png", "pig_hit");

    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/idle.png", "kingPig_idle");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/run.png", "kingPig_run");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/jump.png", "kingPig_jump");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/attack.png", "kingPig_attack");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/dead.png", "kingPig_dead");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/fall.png", "kingPig_fall");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/ground.png", "kingPig_ground");
    texture.load(IMAGE_DIRECTORY + "enemy/kingpig/hit.png", "kingPig_hit");

    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/idle.png", "pigWithBomb_idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/run.png", "pigWithBomb_run");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbomb/throwing.png", "pigWithBomb_throwing");

    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/idle.png", "pigWithBox_idle");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/run.png", "pigWithBox_run");
    texture.load(IMAGE_DIRECTORY + "enemy/pigwithbox/throwing.png", "pigWithBox_throwing");

    texture.load(IMAGE_DIRECTORY + "item/heart/idle.png", "heart_idle");
    texture.load(IMAGE_DIRECTORY + "item/heart/hit.png", "heart_hit");
    texture.load(IMAGE_DIRECTORY + "item/diamond/idle.png", "diamond_idle");
    texture.load(IMAGE_DIRECTORY + "item/diamond/hit.png", "diamond_hit");

    texture.load(IMAGE_DIRECTORY + "item/diamond/idle.png", "diamond_idle");
    texture.load(IMAGE_DIRECTORY + "item/diamond/hit.png", "diamond_hit");

    texture.load(IMAGE_DIRECTORY + "item/door/idle.png", "door_idle");
    texture.load(IMAGE_DIRECTORY + "item/door/open.png", "door_open");
    texture.load(IMAGE_DIRECTORY + "item/door/close.png", "door_close");

    texture.load(IMAGE_DIRECTORY + "item/candle/idle.png", "candle_idle");

    texture.load(IMAGE_DIRECTORY + "item/box/idle.png", "box_idle");
    texture.load(IMAGE_DIRECTORY + "item/box/hit.png", "box_hit");

    texture.load(IMAGE_DIRECTORY + "item/bomb/on.png", "bomb_on");
    texture.load(IMAGE_DIRECTORY + "item/bomb/off.png", "bomb_off");
    texture.load(IMAGE_DIRECTORY + "item/bomb/explode.png", "bomb_explode");

    texture.load(IMAGE_DIRECTORY + "ui/healthbar/healthbar.png", "health_bar");
    texture.load(IMAGE_DIRECTORY + "ui/healthbar/heart.png", "health_heart");

    sound.loadSFX(SOUND_DIRECTORY + "player/attack.wav", "player_attack");
    sound.loadSFX(SOUND_DIRECTORY + "player/dying.wav", "player_dying");
    sound.loadSFX(SOUND_DIRECTORY + "player/jump.wav", "player_jump");

    sound.loadSFX(SOUND_DIRECTORY + "pig/attack.wav", "pig_attack");
    sound.loadSFX(SOUND_DIRECTORY + "pig/dying.wav", "pig_dying");

    sound.loadSFX(SOUND_DIRECTORY + "door/close.wav", "door_close");
    sound.loadSFX(SOUND_DIRECTORY + "door/open.wav", "door_open");

    sound.loadSFX(SOUND_DIRECTORY + "bomb/on.wav", "bomb_on");
    sound.loadSFX(SOUND_DIRECTORY + "bomb/explode.wav", "bomb_explode");

    sound.loadSFX(SOUND_DIRECTORY + "box/break.wav", "box_broken");

    sound.loadSFX(SOUND_DIRECTORY + "heart/bonus.wav", "heart_bonus");

    sound.loadMusic(SOUND_DIRECTORY + "playstate/background.wav", "playstate_background");

    if (!loadLevel()) {
        return false;
    }
    Game::Instance().resetScore();

    /* sound.setVolume(0); */
    sound.playMusic("playstate_background");
    is_loaded_ = true;

    return true;
}

bool PlayState::loadLevel()
{
    exit();

    LevelParser levelParser;
    level_ = levelParser.parseLevel(
        Game::Instance().getLevelPath(Game::Instance().getLevelIndex()).c_str());

    if (level_ == nullptr) {
        return false;
    }

    PhysicWorld::Instance().createContactListener();
    Game::Instance().setLevel(level_.get());
    Camera::Instance().setTarget(level_->getPlayer());
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
    if (!isLoaded() || isPaused() || level_ == nullptr) {
        return;
    }

    if (InputHandler::Instance().isKeyDown(KEY_ESCAPE)) {
        GameStateMachine::Instance().pushState(std::make_unique<PauseState>());
    }

    if (InputHandler::Instance().isKeyDown(KEY_Q)) {
        Game::Instance().toggleDebug();
    };

    PhysicWorld::Instance().update();
    level_->update();
    Camera::Instance().update();
}

void PlayState::render() const
{
    if (!isLoaded() || isPaused() || level_ == nullptr) {
        return;
    }

    level_->render();

    if (Game::Instance().isDebug()) {
        PhysicWorld::Instance().debugDraw();
    }

    renderStatusBar();
}

void PlayState::renderStatusBar() const
{
    TextureManager::Instance().draw("health_bar", {20, 10}, 154, 62);
    for (int i = 0; i < level_->getPlayer()->getHp(); ++i) {
        TextureManager::Instance().draw("health_heart", {60 + i * 25.0f, 30}, 22, 19);
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

    Game::Instance().getWindow()->print(
        "score: " + std::to_string(Game::Instance().getScore()),
        40,
        300 + 400,
        50,
        Color::WHITE);

    Game::Instance().getWindow()->print(
        "highest score: " + std::to_string(Game::Instance().getHighestScore()),
        40,
        300 + 650,
        50,
        Color::WHITE);
}

std::string PlayState::getStateID() const
{
    return kId_;
}
