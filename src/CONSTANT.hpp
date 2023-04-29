#pragma once

#include <box2d/box2d.h>
#include <string>

const std::string CONFIG_FILE = "game_config.json";
const std::string ASSETS_DIRECTORY = "assets/";
const std::string IMAGE_DIRECTORY = "assets/images/";
const std::string SOUND_DIRECTORY = "assets/sounds/";
const std::string FONT_DIRECTORY = "assets/fonts/";
const std::string LEVEL_DIRECTORY = "assets/levels/";


const float PIXEL_PER_METER = 32.0f;
const float METER_PER_PIXEL = 1 / PIXEL_PER_METER;
const float RAD_PER_DEG = 180.0f / b2_pi;
const float DEG_PER_RAD = b2_pi / 180.0f;
const float GROUND_FRICTION = 5.0f;
const float GRAVITY = 10.0f;
