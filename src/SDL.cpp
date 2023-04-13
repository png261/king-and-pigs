#include "SDL.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "Log.hpp"


void SDL::init()
{
    // Will initialize subsystems separatedly

    if (SDL_Init(0) < 0) {
        Log::error("SDL_Init: Couldn't start SDL");
        Log::error(SDL_GetError());
        throw std::runtime_error("SDL Init Fail");
    }

    // Initializing everything related to AUDIO

    if (SDL_WasInit(SDL_INIT_AUDIO) != 0) {
        Log::error("SDL_WasInit: Tried to reinitailize Audio");
        Log::error(SDL_GetError());
        throw std::runtime_error("SDL_WasInit Fail");
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        Log::error("SDL_Init: Couldn't start Audio");
        Log::error(SDL_GetError());
        throw std::runtime_error("SDL_Init Fail");
    }

    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        Log::error("Mix_Init: Couldn't start Audio");
        Log::error(Mix_GetError());
        throw std::runtime_error("Failed to initialize Audio");
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        Log::error("Mix_OpenAudio: Couldn't start Audio");
        Log::error(Mix_GetError());
        throw std::runtime_error("Failed to initialize Audio");
    }

    // Reserving 16 channels (meaning 16 simultaneous SFXs playing)
    Mix_AllocateChannels(16);

    // Initializing everything related to VIDEO

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        Log::error("SDL_WasInit: Tried to reinitailize Video");
        Log::error(SDL_GetError());
        throw std::runtime_error("SDL_WasInit Fail");
    }
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        Log::error("SDL_Init: Couldn't start Video");
        Log::error(SDL_GetError());
        throw std::runtime_error("SDL_Init Fail");
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Log::error("IMG_Init: Couldn't start PNG support");
        Log::error(IMG_GetError());
        throw std::runtime_error("IMG_Init Fail");
    }
    if (TTF_Init() == -1) {
        Log::error("TTF_Init: Couldn't start TTF support");
        Log::error(TTF_GetError());
        throw std::runtime_error("TTF_Init Fail");
    }
};

void SDL::exit()
{
    Mix_AllocateChannels(0);
    Mix_Quit();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
};
