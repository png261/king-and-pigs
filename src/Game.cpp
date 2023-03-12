#include "Game.hpp"

#include "Box2D.hpp"
#include "CONSTANT.hpp"
#include "GameStateMachine.hpp"
#include "InputHandler.hpp"
#include "PlayState.hpp"

Game::Game()
    : m_pWindow(nullptr)
    , m_bRunning(false)
{
    m_levelFiles.push_back(LEVELS_DIR + "level1.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "level2.tmx");
    m_levelFiles.push_back(LEVELS_DIR + "test.tmx");
    m_currentLevel = 0;
}

Game* Game::Instance()
{
    static Game* const s_pInstance = new Game();
    return s_pInstance;
}

bool Game::init(const unsigned int width, const unsigned int height)
{
    if (SDL::init() == false) {
        return false;
    };

    m_pWindow = new Window(width, height);

    if (Box2D::Instance()->init() == false) {
        return false;
    };

    GameStateMachine::Instance()->changeState(new PlayState());
    m_bRunning = true;

    return true;
}

void Game::handleEvents()
{
    InputHandler::Instance()->update();
    Box2D::Instance()->handleEvents();
}

void Game::update()
{
    GameStateMachine::Instance()->update();
    Box2D::Instance()->update();
}

void Game::render()
{
    m_pWindow->clear();

    GameStateMachine::Instance()->render();
    Box2D::Instance()->debugDraw();

    m_pWindow->refresh();
    m_pWindow->delayFramerateIfNeeded();
}

void Game::clean()
{
    Box2D::Instance()->clean();
    delete m_pWindow;
    SDL::exit();
}

void Game::quit()
{
    m_bRunning = false;
}

void Game::nextLevel()
{
    m_currentLevel += 1;
    if (m_currentLevel >= m_levelFiles.size()) {
        /* TODO: win screen */
        return;
    }

    GameStateMachine::Instance()->changeState(new PlayState());
}

int Game::getCurrentLevel() const
{
    return m_currentLevel;
}

bool Game::isRunning() const
{
    return m_bRunning;
}


std::string Game::getLevel(int index)
{
    return m_levelFiles[index];
}

Window* Game::getWindow()
{
    return m_pWindow;
}
