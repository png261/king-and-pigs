#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.f / FPS;

int main(int argc, char* argv[])
{
    if (!Game::Instance()->init("kings and pigs", 200, 0, 700, 400, SDL_WINDOW_SHOWN)) {
        return -1;
    }

    Uint32 frameStart, frameTime;

    while (Game::Instance()->running()) {
        frameStart = SDL_GetTicks();

        Game::Instance()->handleEvents();
        Game::Instance()->update();
        Game::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME) {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
    Game::Instance()->clean();
    return 0;
}
