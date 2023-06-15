#pragma once

#include <box2d/box2d.h>
#include <string>

const std::string CONFIG_FILE = data/game_config.json;
const std::string IMAGE_DIRECTORY = data/images/;
const std::string SOUND_DIRECTORY = data/sounds/;
const std::string FONT_DIRECTORY = data/fonts/;
const std::string LEVEL_DIRECTORY = data/levels/;
const std::string ICON_DIRECTORY = data/icon/;

const float PIXEL_PER_METER = 32.0f;
const float METER_PER_PIXEL = 1 / PIXEL_PER_METER;
const float RAD_PER_DEG = 180.0f / b2_pi;
const float DEG_PER_RAD = b2_pi / 180.0f;
const float GROUND_FRICTION = 5.0f;
const float GRAVITY = 10.0f;

const std::string ONE_WAY_TYPE = "oneway";
