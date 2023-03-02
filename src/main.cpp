#include "Game.hpp"

int main(int argc, char* argv[])
{
    if (!Game::Instance()->init(700, 400)) {
        return -1;
    }

    while (Game::Instance()->isRunning()) {
        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();
    }

    Game::Instance()->clean();
    return 0;
}
