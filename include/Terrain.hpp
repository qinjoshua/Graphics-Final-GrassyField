/** @file Terrain.hpp
 *  @brief Create a terrain
 *
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Object.hpp"

#include <vector>
#include <string>
#include <future>
#include <PerlinNoise/PerlinNoise.hpp>

class Terrain : public Object {
public:
    // Takes in a Terrain and a filename for the heightmap.
    Terrain (unsigned int boxWidth, std::string fileName);
    // Destructor
    ~Terrain ();
    // override the initilization routine.
    void Init();
    // Loads a heightmap based on a PPM image
    // This then sets the heights of the terrain.
    void LoadHeightMap();
    // Load textures
    void LoadTextures(std::string colormap, std::string detailmap);

    // Computes the height of a given x and y coordinate
    float ComputeHeight(int x, int y);

    // Moves the position of the camera to the given location
    void MoveCamera(int x, int y);

    void ScrewBuffer();

private:
    // data
    unsigned int m_xSegments;
    unsigned int m_zSegments;

    unsigned int m_boxWidth;
    unsigned int m_renderAreaWidth;

    int m_xPos = 0;
    int m_zPos = 0;

    // Store the height in a multidimensional array
    float* m_heightData;

    const siv::PerlinNoise::seed_type seed = 123456u;
    const siv::PerlinNoise perlin{ seed };

    // Stores the x and z indices of the box that the player is currently in
    int m_boxXIndex;
    int m_boxZIndex;

    int ToActualXPosition(int x);
    int ToActualZPosition(int z);

    std::future<void> fut;

    void UpdateHeightMap(int xOffset, int zOffset);
};

#endif
