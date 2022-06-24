#include "Terrain.hpp"
#include "Constants.hpp"
#include "Image.hpp"

#include <iostream>
#include <math.h>

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int xSegs, unsigned int zSegs, std::string fileName) :
                m_xSegments(xSegs), m_zSegments(zSegs) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    m_BoxXPos = PLAYER_START_X_POS / BOX_SIZE * BOX_SIZE - BOX_SIZE;
    m_BoxZPos = PLAYER_START_Z_POS / BOX_SIZE * BOX_SIZE - BOX_SIZE;

    // Load up some image data
    Image heightMap(fileName);
    heightMap.LoadPPM(true);
    // Set the height data for the image
    // TODO: Currently there is a 1-1 mapping between a pixel and a segment
    // You might consider interpolating values if there are more segments
    // than pixels.
    float scale = 5.0f; // Note that this scales down the values to make
                        // the image a bit more flat.
    // Create height data
    m_heightData = new float[m_xSegments*m_zSegments];
    // Set the height data equal to the grayscale value of the heightmap
    // Because the R,G,B will all be equal in a grayscale iamge, then
    // we just grab one of the color components.

    LoadHeightMap();

    // Initialize the terrain
    Init();
}

// Destructor
Terrain::~Terrain(){
    // Delete our allocatted heightmap data
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void Terrain::Init(){
    // Create the initial grid of vertices.

    // Build grid of vertices!
    for(unsigned int z=0; z < m_zSegments; ++z){
        for(unsigned int x =0; x < m_xSegments; ++x){
            float u = 1.0f - ((float)x/(float)m_xSegments);
            float v = 1.0f - ((float)z/(float)m_zSegments);
            // Calculate the correct position and add the texture coordinates
            m_geometry.AddVertex(x * TERRAIN_UNIT_SIZE + m_xOffset * TERRAIN_UNIT_SIZE, m_heightData[x+z*m_xSegments],z * TERRAIN_UNIT_SIZE + m_zOffset, u,v);
        }
    }

    /*for(unsigned int z=m_BoxZPos - Box_Size; z < m_BoxZPos + Box_Size * 2; ++z){
        for(unsigned int x =0; x < m_xSegments; ++x){
            float u = 1.0f - ((float)x/(float)m_xSegments);
            float v = 1.0f - ((float)z/(float)m_zSegments);
            // Calculate the correct position and add the texture coordinates
            m_geometry.AddVertex(x * TERRAIN_UNIT_SIZE + m_xOffset * TERRAIN_UNIT_SIZE, m_heightData[x+z*m_xSegments],z * TERRAIN_UNIT_SIZE + m_zOffset, u,v);
        }
    }*/

    // Figure out which indices make up each triangle
    // By writing out a few of the indicies you can figure out
    // the pattern here. Note there is an offset.

    // Build triangle strip
    for(unsigned int z=0; z < m_zSegments-1; ++z){
        for(unsigned int x =0; x < m_xSegments-1; ++x){
            m_geometry.AddIndex(x+(z*m_zSegments));
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
            m_geometry.AddIndex(x+(z*m_zSegments+1));

            m_geometry.AddIndex(x+(z*m_zSegments)+1);
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments);
            m_geometry.AddIndex(x+(z*m_zSegments)+m_xSegments+1);
        }
    }


   // Finally generate a simple 'array of bytes' that contains
   // everything for our buffer to work with.
   m_geometry.Gen();
   // Create a buffer and set the stride of information
   m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());
}

// Builds the heights of the terrain from perlin noise
void Terrain::LoadHeightMap(){
    // populate heightData
    for (unsigned int z = 0; z < m_zSegments; ++z) {
        for (unsigned int x = 0; x < m_xSegments; ++x) {
            m_heightData[x + z * m_xSegments] = ComputeHeight(x + m_xOffset, z + m_zOffset);
        }
    }
}

// TODO: Instead of re-drawing the terrain at every iteration, do this instead:
// 1) Create a new function called UpdateHeightMap
// 2) Move the existing positions in the array by how much the xDelta and yDelta are
// 3) Update only the cells of the array that need to be updated
void Terrain::MoveCamera(int x, int z) {
    int xDelta = x - m_xOffset;
    int zDelta = z - m_xOffset;

    m_xOffset = x / TERRAIN_UNIT_SIZE;
    m_zOffset = z / TERRAIN_UNIT_SIZE;

    // Uncomment this to load every turn
    LoadHeightMap();
    Init();
}

void Terrain::LoadTextures(std::string colormap, std::string detailmap){
        // Load our actual textures
        m_textureDiffuse.LoadTexture(colormap); // Found in object
        m_detailMap.LoadTexture(detailmap);     // Found in object
}

// Code inspired by this handy demonstration:
// https://www.youtube.com/watch?v=U9q-jM3-Phc&t=9s&ab_channel=SimonDev
float Terrain::ComputeHeight(int x, int y) {
    const float xs = x / TERRAIN_SCALE;
    const float ys = y / TERRAIN_SCALE;
    const float G = 2.0 * (-TERRAIN_PERSISTENCE);

    float amplitude = 1.0f;
    float frequency = 1.0f;
    float normalization = 0.0f;
    float total = 0.0f;

    for (int o = 0; o < TERRAIN_OCTAVES; o++) {
        const double noise = perlin.octave2D_01((xs * frequency), (ys * frequency), 4);
        total += noise * amplitude;
        normalization += amplitude;
        amplitude *= G;
        frequency *= TERRAIN_LACUNARITY;
    }

    total /= normalization;
    return pow(total, TERRAIN_EXPONENTIATION) * TERRAIN_HEIGHT;
}
