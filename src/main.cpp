#include "Game.hpp"

#include "Log.hpp"

int main()
{
    Game& game = Game::Instance();
    try {
        game.init();
        while (game.isRunning()) {
            game.handleEvents();
            game.update();
            game.render();
        }
        game.clean();
    } catch (std::exception const& exeption) {
        Log::error("Exception caught:\n" + std::string(exeption.what()) + "\nQuitting...");
        return -1;
    }
    return 0;
}
