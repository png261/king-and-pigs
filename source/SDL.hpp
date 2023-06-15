#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "SDL2_gfxPrimitives.hpp"

namespace SDL {
void init();
void initAudio();
void initVideo();
void initFont();

void quit();
void quitAudio();
void quitFont();

void hideCursor();
}; // namespace SDL
