#include "SDL.hpp"
#include "Log.hpp"


bool SDL::init()
{
    // Will initialize subsystems separatedly

    if (SDL_Init(0) < 0) {
        Log::error("SDL_Init: Couldn't start SDL");
        Log::error(std::string(SDL_GetError()));
        return false;
    }

    // Initializing everything related to AUDIO

    if (SDL_WasInit(SDL_INIT_AUDIO) != 0) {
        Log::error("SDL_WasInit: Tried to reinitailize Audio");
        Log::error(SDL_GetError());
        return false;
    }

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        Log::error("SDL_Init: Couldn't start Audio");
        Log::error(std::string(SDL_GetError()));
        return false;
    }

    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        Log::warning("Mix_Init: Couldn't start Audio");
        Log::warning(Mix_GetError());
    }

    if (-1 == Mix_OpenAudio(
                  MIX_DEFAULT_FREQUENCY, // audio rate
                  MIX_DEFAULT_FORMAT, // format
                  2, // channels
                  4096)) // buffers
    {
        Log::warning("Mix_OpenAudio: Couldn't start Audio");
        Log::warning(Mix_GetError());
    }

    // Reserving 16 channels (meaning 16 simultaneous SFXs playing)
    Mix_AllocateChannels(16);

    // Initializing everything related to VIDEO

    if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        Log::error("SDL_WasInit: Tried to reinitailize Video");
        Log::error(std::string(SDL_GetError()));
        return false;
    }
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        Log::error("SDL_Init: Couldn't start Video");
        Log::error(std::string(SDL_GetError()));
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        Log::error("IMG_Init: Couldn't start PNG support");
        Log::error(std::string(IMG_GetError()));
        return false;
    }
    if (TTF_Init() == -1) {
        Log::error("TTF_Init: Couldn't start TTF support");
        Log::error(std::string(TTF_GetError()));
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
