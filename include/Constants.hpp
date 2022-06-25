#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
/** @file constants.hpp
 *  @brief Stores constants for our program.
 *
 *  @author Joshua Qin
 *  @bug No known bugs.
 */

#include <stdint.h>

class Constants {
public:
	static /*const*/ inline float TERRAIN_UNIT_SIZE = 5;

	static /*const*/ inline uint8_t TERRAIN_SEED = 123456u;
	static /*const*/ inline float TERRAIN_SCALE = 500;
	static /*const*/ inline float TERRAIN_PERSISTENCE = 0.5;
	static /*const*/ inline uint8_t TERRAIN_OCTAVES = 1;
	static /*const*/ inline float TERRAIN_LACUNARITY = 1;
	static /*const*/ inline float TERRAIN_EXPONENTIATION = 3.7;
	static /*const*/ inline float TERRAIN_HEIGHT = 150;

	static /*const*/ inline int TERRAIN_BOX_SIZE = 128;

	static /*const*/ inline float EYES_HEIGHT = 10;
	static /*const*/ inline int PLAYER_START_X_POS = 100;
	static /*const*/ inline int PLAYER_START_Z_POS = 100;
	static /*const*/ inline int SPACE_HEIGHT = 256;
	static /*const*/ inline int SPACE_WIDTH = 256;
};

#endif