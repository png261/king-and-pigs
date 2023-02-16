#include "SDL.hpp"
#include "Log.hpp"


bool SDL::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Log::error("fail to init SDL");
        return false;
    }
    return true;
};

void SDL::exit()
{
    Mix_AllocateChannels(0);

    Mix_Quit();
    Mix_CloseAudio();

    if (TTF_WasInit()) TTF_Quit();

    SDL_Quit();
};
