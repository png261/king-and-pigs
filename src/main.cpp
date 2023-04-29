#include "CONSTANT.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "Utils.hpp"

int main(int, char*[])
{
    try {
        const Json::Value& config = Utils::read_json_file(CONFIG_FILE);
        const int width = config["width"].asInt();
        const int height = config["height"].asInt();
        const std::string title = config["title"].asString();
        const bool is_debug = config["debug"].asBool();

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
