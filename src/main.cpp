#include "Game.hpp"
#include "Log.hpp"

int main()
{
    try {
        Game& game = Game::Instance();
        game.init();
        while (game.isRunning()) {
            game.handleEvents();
            game.update();
            game.render();
        }
        game.clean();
    } catch (const std::exception& exception) {
        Log::error("Exception caught:\n" + std::string(exception.what()) + "\nQuitting...");
        return -1;
    }
    return 0;
}
