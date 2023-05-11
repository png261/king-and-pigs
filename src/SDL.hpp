#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h> 
#include <SDL_ttf.h> 
#include "SDL2_gfxPrimitives.hpp" 

namespace SDL {
void init();
void exit();
void hideCursor();
}; // namespace SDL
