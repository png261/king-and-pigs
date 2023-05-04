#pragma once

#include <SDL.h> // SDL2
#include <SDL_image.h> // SDL2_Image
#include <SDL_mixer.h> // SDL2_Mixer
#include <SDL_ttf.h> // SDL2_TTF

#include "SDL2_gfxPrimitives.hpp" // SDL2_GFX
namespace SDL {
void init();
void exit();
void hideCursor();
}; // namespace SDL
