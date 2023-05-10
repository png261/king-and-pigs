#include "HowToPlayState.hpp"

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
#include "Utils.hpp"

const std::string HowToPlayState::kStateID_ = "HOW_TO_PLAY_STATE";

HowToPlayState::HowToPlayState()
    : is_enter_main_menu(false){};

bool HowToPlayState::enter()
{
    is_loaded_ = false;

    TextureManager::Instance().load(
        IMAGE_DIRECTORY + "ui/how_to_play/background.png",
        "how_to_play_background");

    const int button_width = 100;
    const int button_height = 50;
    auto back_button = std::make_unique<Button>();
    back_button->setTitle("back");
    back_button->load(std::make_unique<LoaderParams>(
        Game::Instance().getWindow()->getCenter().x - 400,
        Game::Instance().getWindow()->getCenter().y - 300,
        button_width,
        button_height));
    back_button->onClick([this]() { is_enter_main_menu = true; });
    ui_objects_.push_back(std::move(back_button));

    is_loaded_ = true;
    return true;
};

void HowToPlayState::update()
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    if (is_enter_main_menu || InputManager::Instance().isKeyDown(KEY_ESCAPE) ||
        InputManager::Instance().isKeyDown(KEY_Q)) {
        GameStateManager::Instance().changeState(std::make_unique<MainMenuState>());
        return;
    }

    for (const auto& obj : ui_objects_) {
        obj->update();
    }
};

void HowToPlayState::render() const
{
    if (!isLoaded() || isPaused()) {
        return;
    }

    Game::Instance().getWindow()->fill(Utils::hexToRgba("#3f3851"));
    TextureManager::Instance().draw(
        "how_to_play_background",
        Game::Instance().getWindow()->getCenter() - 0.5 * b2Vec2(416, 416),
        416,
        416);

    const int x = Game::Instance().getWindow()->getCenter().x;
    const int y = Game::Instance().getWindow()->getCenter().y - 80;
    const int margin_y = 50;
    const int font_size = 30;

    Game::Instance()
        .getWindow()
        ->print("Controls", x, y - 80, font_size + 10, ColorName::BLACK, FontStyle::UNDERLINE);
    Game::Instance().getWindow()->print("Move right: Arrow right, D", x, y, font_size);
    Game::Instance().getWindow()->print("Move left: Arrow left, A", x, y + margin_y * 1, font_size);
    Game::Instance().getWindow()->print("Enter door: Arrow up, W", x, y + margin_y * 2, font_size);
    Game::Instance().getWindow()->print("Jump: Mouse left, K", x, y + margin_y * 3, font_size);
    Game::Instance().getWindow()->print("Attack: Mouse right, J", x, y + margin_y * 4, font_size);

    for (const auto& obj : ui_objects_) {
        obj->draw();
    }
};

bool HowToPlayState::exit()
{
    pause();
    InputManager::Instance().reset();
    return true;
};

std::string HowToPlayState::getStateID() const
{
    return kStateID_;
};
