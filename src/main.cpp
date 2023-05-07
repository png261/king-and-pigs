#include "CONSTANT.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Utils.hpp"

int main(int, char*[])
{
    try {
        const auto& config = Utils::read_json_file(CONFIG_FILE);
        const auto width = config["width"].get<int>();
        const auto height = config["height"].get<int>();
        const auto title = config["title"].get<std::string>();
        const auto is_debug = config["debug"].get<bool>();

        Game& game = Game::Instance();
        game.init(width, height, title);
        game.debugMode(is_debug);

        while (game.isRunning()) {
            game.handleEvents();
            game.update();
            game.render();
            game.handleFPS();
        }

        game.clean();
    } catch (const std::exception& exception) {
        Log::error("Exception caught:\n" + std::string(exception.what()) + "\nQuitting...");
        return -1;
    }

    return 0;
}
