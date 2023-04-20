#pragma once

#include <SDL2/SDL.h> // SDL2
#include <SDL2/SDL_image.h> // SDL2_Image
#include <SDL2/SDL_mixer.h> // SDL2_Mixer
#include <SDL2/SDL_ttf.h> // SDL2_TTF

namespace SDL {
void init();
void exit();
void hideCursor();
}; // namespace SDL
