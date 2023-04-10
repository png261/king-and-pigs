#include "Game.hpp"

int main(int argc, char* argv[])
{
    Game& game = Game::Instance();

    if (game.init() == false) {
        return -1;
    }

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;
}
