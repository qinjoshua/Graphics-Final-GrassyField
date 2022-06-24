#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
/** @file Constants.hpp
 *  @brief Stores constants for our program.
 *
 *  @author Joshua Qin
 *  @bug No known bugs.
 */

#include <stdint.h>

static const float TERRAIN_UNIT_SIZE = 4;
static const uint8_t TERRAIN_SEED = 123456u;
static const float TERRAIN_SCALE = 200;
static const float TERRAIN_PERSISTENCE = 0.5;
static const uint8_t TERRAIN_OCTAVES = 1;
static const float TERRAIN_LACUNARITY = 1.5;
static const float TERRAIN_EXPONENTIATION = 2.0;
static const float TERRAIN_HEIGHT = 300;
static const float EYES_HEIGHT = 100;
static const int PLAYER_START_X_POS = 100;
static const int PLAYER_START_Z_POS = 100;
static const int BOX_SIZE = 128;
static const int SPACE_HEIGHT = 128;
static const int SPACE_WIDTH = 128;


#endif