#include "SDL.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "Log.hpp"


void SDL::init()
{
    // Will initialize subsystems separatedly

    if (SDL_Init(0) < 0) {
        throw std::runtime_error("SDL_Init: Couldn't start SDL" + std::string(SDL_GetError()));
    }

    // Initializing everything related to AUDIO

    if (SDL_WasInit(SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error(
            "SDL_WasInit: Tried to reinitailize Audio" + std::string(SDL_GetError()));
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("SDL_Init: Couldn't start Audio" + std::string(SDL_GetError()));
    }

    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        throw std::runtime_error("Mix_Init: Couldn't start Audio" + std::string(Mix_GetError()));
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        throw std::runtime_error(
            "Mix_OpenAudio: Couldn't start Audio" + std::string(Mix_GetError()));
    }

    // Reserving 16 channels (meaning 16 simultaneous SFXs playing)
    Mix_AllocateChannels(16);

    // Initializing everything related to VIDEO

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(
            "SDL_WasInit: Tried to reinitailize Video" + std::string(SDL_GetError()));
    }
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL_Init: Couldn't start Video" + std::string(SDL_GetError()));
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw std::runtime_error(
            "IMG_Init: Couldn't start PNG support" + std::string(IMG_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error(
            "TTF_Init: Couldn't start TTF support" + std::string(TTF_GetError()));
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
