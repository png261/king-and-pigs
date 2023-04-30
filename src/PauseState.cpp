#include "PauseState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

const std::string PauseState::kId_ = "PAUSE";

PauseState::PauseState()
    : is_enterResume_(false)
    , is_enter_main_menu(false){};

void PauseState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enterResume_) {
        GameStateMachine::Instance().popState();
        return;
    }
    if (is_enter_main_menu) {
        GameStateMachine::Instance().popState();
        GameStateMachine::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    if (InputHandler::Instance().isKeyDown(KEY_ESCAPE)) {
        is_enterResume_ = true;
    }

    for (const auto& obj : ui_objects_) {
        obj->update();
    }
};

void PauseState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    Game::Instance().getWindow()->drawOverlay({0, 0, 0, 100});
    for (const auto& obj : ui_objects_) {
        obj->draw();
    }
};

bool PauseState::enter()
{
    is_loaded_ = false;

    TextureManager& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "ui/button/muteSFX.png", "icon mute_sfx");
    texture.load(IMAGE_DIRECTORY + "ui/button/muteMusic.png", "icon mute_music");

    const int centerX = Game::Instance().getWindow()->getCenter().x;
    const int centerY = Game::Instance().getWindow()->getCenter().y;

    auto resume_button = std::make_unique<Button>();
    resume_button->setTitle("Resume");
    resume_button->load(
        std::make_unique<LoaderParams>(centerX - 300 * 0.5f, centerY - 70 * 0.5f, 300, 70));
    resume_button->onClick([this]() { is_enterResume_ = true; });

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(
        std::make_unique<LoaderParams>(centerX - 300 * 0.5f, centerY - 70 * 0.5f + 100, 300, 70));
    main_menu_button->onClick([this]() { is_enter_main_menu = true; });

    auto mute_sfx = std::make_unique<Button>();
    mute_sfx->setTexture("icon mute_sfx");
    mute_sfx->load(std::make_unique<LoaderParams>(centerX - 50 - 20, centerY + 200, 50, 50));
    mute_sfx->onClick([this]() { SoundManager::Instance().toggleMuteSFX(); });

    auto mute_music = std::make_unique<Button>();
    mute_music->setTexture("icon mute_music");
    mute_music->load(std::make_unique<LoaderParams>(centerX + 20, centerY + 200, 50, 50));
    mute_music->onClick([this]() { SoundManager::Instance().toggleMuteMusic(); });

    ui_objects_.push_back(std::move(resume_button));
    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(mute_sfx));
    ui_objects_.push_back(std::move(mute_music));

    is_loaded_ = true;
    return true;
};

bool PauseState::exit()
{
    pause();
    InputHandler::Instance().reset();
    return true;
};

std::string PauseState::getStateID() const
{
    return kId_;
};
