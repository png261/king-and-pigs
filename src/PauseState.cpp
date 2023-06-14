#include "PauseState.hpp"

#include "Button.hpp"
#include "CONSTANT.hpp"
#include "Game.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "Log.hpp"
#include "MainMenuState.hpp"
#include "PlayState.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

const std::string PauseState::kStateID_ = "PAUSE_STATE";

PauseState::PauseState()
    : is_enterResume_(false)
    , is_enter_main_menu(false){};

bool PauseState::enter()
{
    is_loaded_ = false;

    auto& texture = TextureManager::Instance();
    texture.load(IMAGE_DIRECTORY + "ui/pause_state/mute_sfx.png", "icon mute_sfx");
    texture.load(IMAGE_DIRECTORY + "ui/pause_state/mute_music.png", "icon mute_music");

    const int x = Game::Instance().getWindow()->getCenter().x;
    const int y = Game::Instance().getWindow()->getCenter().y;
    const int width = 300;
    const int height = 70;
    const int margin_y = 100;

    auto resume_button = std::make_unique<Button>();
    resume_button->setTitle("Resume");
    resume_button->load(LoaderParams(x - width * 0.5f, y - height * 0.5f, width, height));
    resume_button->onClick([this]() { is_enterResume_ = true; });

    auto main_menu_button = std::make_unique<Button>();
    main_menu_button->setTitle("Main Menu");
    main_menu_button->load(
        LoaderParams(x - width * 0.5f, y - height * 0.5f + margin_y, width, height));
    main_menu_button->onClick([this]() { is_enter_main_menu = true; });

    auto mute_sfx_button = std::make_unique<Button>();
    mute_sfx_button->setTexture("icon mute_sfx");
    mute_sfx_button->load(LoaderParams(x - 50 - 20, y + 200, 50, 50));
    mute_sfx_button->onClick([]() { SoundManager::Instance().toggleMuteSFX(); });

    auto mute_music_button = std::make_unique<Button>();
    mute_music_button->setTexture("icon mute_music");
    mute_music_button->load(LoaderParams(x + 20, y + 200, 50, 50));
    mute_music_button->onClick([]() { SoundManager::Instance().toggleMuteMusic(); });

    ui_objects_.push_back(std::move(resume_button));
    ui_objects_.push_back(std::move(main_menu_button));
    ui_objects_.push_back(std::move(mute_sfx_button));
    ui_objects_.push_back(std::move(mute_music_button));

    is_loaded_ = true;
    return true;
};

void PauseState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enterResume_) {
        GameStateManager::Instance().popState();
        return;
    }
    if (is_enter_main_menu) {
        GameStateManager::Instance().clean();
        GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    if (InputManager::Instance().isKeyDown(KEY_ESCAPE)) {
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


bool PauseState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string PauseState::getStateID() const
{
    return kStateID_;
};
