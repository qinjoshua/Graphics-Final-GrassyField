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
static const float TERRAIN_LACUNARITY = 2.0;
static const float TERRAIN_EXPONENTIATION = 2.0;
static const float TERRAIN_HEIGHT = 300;
static const float BOX_SIZE = 900;

#endif