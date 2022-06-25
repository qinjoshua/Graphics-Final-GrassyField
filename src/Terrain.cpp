#include "Terrain.hpp"
#include "Constants.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include <iostream>
#include <future>
#include <math.h>

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Constructor for our object
// Calls the initialization method
Terrain::Terrain(unsigned int boxWidth, std::string fileName) :
                m_boxWidth(boxWidth), m_renderAreaWidth(boxWidth * 3) {
    std::cout << "(Terrain.cpp) Constructor called \n";

    m_boxXIndex = Constants::PLAYER_START_X_POS / Constants::TERRAIN_UNIT_SIZE / m_boxWidth;
    m_boxZIndex = Constants::PLAYER_START_Z_POS / Constants::TERRAIN_UNIT_SIZE / m_boxWidth;

    m_xPos = Constants::PLAYER_START_X_POS;
    m_zPos = Constants::PLAYER_START_Z_POS;

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
    m_heightData = new float[m_boxWidth * m_boxWidth * 9];

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
    std::cout << Constants::TERRAIN_SCALE << std::endl;
    // Create the initial grid of vertices.
    m_geometry = Geometry();
    m_vertexBufferLayout = VertexBufferLayout();

    // Build grid of vertices!
    for(unsigned int z=0; z < m_renderAreaWidth; ++z){
        for(unsigned int x =0; x < m_renderAreaWidth; ++x){
            float u = 1.0f - ((float)x/(float)m_renderAreaWidth);
            float v = 1.0f - ((float)z/(float)m_renderAreaWidth);
            // Calculate the correct position and add the texture coordinates
            m_geometry.AddVertex(ToActualXPosition(x), m_heightData[x+z*(m_renderAreaWidth)],ToActualZPosition(z), u,v);
        }
    }

    /*for(unsigned int z=m_BoxZPos - Box_Size; z < m_BoxZPos + Box_Size * 2; ++z){
        for(unsigned int x =0; x < m_renderAreaWidth; ++x){
            float u = 1.0f - ((float)x/(float)m_renderAreaWidth);
            float v = 1.0f - ((float)z/(float)m_renderAreaWidth);
            // Calculate the correct position and add the texture coordinates
            m_geometry.AddVertex(x * TERRAIN_UNIT_SIZE + m_xOffset * TERRAIN_UNIT_SIZE, m_heightData[x+z*m_renderAreaWidth],z * TERRAIN_UNIT_SIZE + m_zOffset, u,v);
        }
    }*/

    // Figure out which indices make up each triangle
    // By writing out a few of the indicies you can figure out
    // the pattern here. Note there is an offset.

    // Build triangle strip
    for(unsigned int z=0; z < m_renderAreaWidth-1; ++z){
        for(unsigned int x =0; x < m_renderAreaWidth-1; ++x){
            m_geometry.AddIndex(x+(z*m_renderAreaWidth));
            m_geometry.AddIndex(x+(z*m_renderAreaWidth)+m_renderAreaWidth);
            m_geometry.AddIndex(x+(z*m_renderAreaWidth+1));

            m_geometry.AddIndex(x+(z*m_renderAreaWidth)+1);
            m_geometry.AddIndex(x+(z*m_renderAreaWidth)+m_renderAreaWidth);
            m_geometry.AddIndex(x+(z*m_renderAreaWidth)+m_renderAreaWidth+1);
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
    for (unsigned int z = 0; z < m_renderAreaWidth; ++z) {
        for (unsigned int x = 0; x < m_renderAreaWidth; ++x) {
            m_heightData[x + (z * m_renderAreaWidth)] = ComputeHeight(ToActualXPosition(x), ToActualZPosition(z));
        }
    }
}

// The offsets represent how many places existing data needs to be moved, negative for left and positive for right
void Terrain::UpdateHeightMap(int xOffset, int zOffset) {
    
    int xLower = xOffset > 0 ? xOffset * m_boxWidth : 0;
    int xUpper = xOffset < 0 ? (int)m_renderAreaWidth + xOffset * (int)m_boxWidth : m_renderAreaWidth;
    int zLower = zOffset > 0 ? zOffset * m_boxWidth : 0;
    int zUpper = zOffset < 0 ? (int)m_renderAreaWidth + zOffset * (int)m_boxWidth : m_renderAreaWidth;
    
    // temporary heightData to cache values
    float* heightData = new float[m_boxWidth * m_boxWidth * 9];

    for (unsigned int z = 0; z < m_renderAreaWidth; ++z) {
        for (unsigned int x = 0; x < m_renderAreaWidth; ++x) {
            // This means that this point is in the old array - no need to recalculate
            if (x >= xLower && x < xUpper && z >= zLower && z < zUpper) {
                heightData[x + (z * m_renderAreaWidth)] = m_heightData[(x-(xOffset * (int)m_boxWidth)) + ((z-(zOffset * (int)m_boxWidth)) * m_renderAreaWidth)];
            }
            else {
                heightData[x + (z * m_renderAreaWidth)] = ComputeHeight(ToActualXPosition(x), ToActualZPosition(z));
            }
        }
    }

    // Copy all the data over
    /*for (unsigned int z = 0; z < m_renderAreaWidth; ++z) {
        for (unsigned int x = 0; x < m_renderAreaWidth; ++x) {
            m_heightData[x + (z * m_renderAreaWidth)] = heightData[x + (z * m_renderAreaWidth)];
        }
    }*/

    delete[] m_heightData;
    m_heightData = heightData;
}

int Terrain::ToActualXPosition(int x) {
    return Constants::TERRAIN_UNIT_SIZE * ((m_boxXIndex - 1) * (int)m_boxWidth + x);
}

int Terrain::ToActualZPosition(int z) {
    return Constants::TERRAIN_UNIT_SIZE * ((m_boxZIndex - 1) * (int)m_boxWidth + z);
}

// TODO: Instead of re-drawing the terrain at every iteration, do this instead:
// 1) Create a new function called UpdateHeightMap
// 2) Move the existing positions in the array by how much the xDelta and yDelta are
// 3) Update only the cells of the array that need to be updated
void Terrain::MoveCamera(int x, int z) {
    int boxXIndex = x >= 0 ? x / Constants::TERRAIN_UNIT_SIZE / m_boxWidth : x / Constants::TERRAIN_UNIT_SIZE / m_boxWidth - 1;
    int boxZIndex = z >= 0 ? z / Constants::TERRAIN_UNIT_SIZE / m_boxWidth : z / Constants::TERRAIN_UNIT_SIZE / m_boxWidth - 1;

    int xOffset = (int)m_boxXIndex - (int)boxXIndex;
    int zOffset = (int)m_boxZIndex - (int)boxZIndex;

    if (xOffset != 0 || zOffset != 0) {
        std::cout << "Hi I'm here" << std::endl;
        m_boxXIndex = boxXIndex;
        m_boxZIndex = boxZIndex;
        UpdateHeightMap(xOffset, zOffset);
        
        //fut.wait();
        //fut = std::async(std::launch::async, [&]{ Init(); });
        Init();
    }
}

void Terrain::LoadTextures(std::string colormap, std::string detailmap){
        // Load our actual textures
        m_textureDiffuse.LoadTexture(colormap); // Found in object
        m_detailMap.LoadTexture(detailmap);     // Found in object
}

// Code inspired by this handy demonstration:
// https://www.youtube.com/watch?v=U9q-jM3-Phc&t=9s&ab_channel=SimonDev
float Terrain::ComputeHeight(int x, int y) {
    const float xs = x / Constants::TERRAIN_SCALE;
    const float ys = y / Constants::TERRAIN_SCALE;
    const float G = pow(2.0, (-Constants::TERRAIN_PERSISTENCE));

    float amplitude = 1.0f;
    float frequency = 1.0f;
    float normalization = 0.0f;
    float total = 0.0f;

    for (int o = 0; o < Constants::TERRAIN_OCTAVES; o++) {
        const double noise = perlin.octave2D_01((xs * frequency), (ys * frequency), 4);
        total += noise * amplitude;
        normalization += amplitude;
        amplitude *= G;
        frequency *= Constants::TERRAIN_LACUNARITY;
    }

    total /= normalization;
    return pow(total, Constants::TERRAIN_EXPONENTIATION) * Constants::TERRAIN_HEIGHT;
}

void Terrain::UpdateShader(Shader* m_shader, glm::mat4 projectionMatrix, Camera* camera, Transform m_worldTransform) {
    // For our object, we apply the texture in the following way
    // Note that we set the value to 0, because we have bound
    // our texture to slot 0.
    std::cout << "I am updating in Terrain" << std::endl;
    m_shader->Bind();
    m_shader->SetUniform1i("u_DiffuseMap",0);
    // TODO: This assumes every SceneNode is a 'Terrain' so this shader setup code
    //       needs to be moved preferably to 'Object' or 'Terrain'
    m_shader->SetUniform1i("u_DetailMap",1);
    // Set the MVP Matrix for our object
    // Send it into our shader
    m_shader->SetUniformMatrix4fv("model", &m_worldTransform.GetInternalMatrix()[0][0]);
    m_shader->SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
    m_shader->SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);

    // Create a 'light'
    // Create a first 'light'
    m_shader->SetUniform3f("pointLights[0].lightColor",1.0f,1.0f,1.0f);
    m_shader->SetUniform3f("pointLights[0].lightPos",
                           camera->GetEyeXPosition() + camera->GetViewXDirection(),
                           camera->GetEyeYPosition() + camera->GetViewYDirection(),
                           camera->GetEyeZPosition() + camera->GetViewZDirection());
    m_shader->SetUniform1f("pointLights[0].ambientIntensity",0.9f);
    m_shader->SetUniform1f("pointLights[0].specularStrength",0.5f);
    m_shader->SetUniform1f("pointLights[0].constant",1.0f);
    m_shader->SetUniform1f("pointLights[0].linear",0.003f);
    m_shader->SetUniform1f("pointLights[0].quadratic",0.0f);

    // Create a second light
    m_shader->SetUniform3f("pointLights[1].lightColor",1.0f,0.0f,0.0f);
    m_shader->SetUniform3f("pointLights[1].lightPos",
                           camera->GetEyeXPosition() + camera->GetViewXDirection(),
                           camera->GetEyeYPosition() + camera->GetViewYDirection(),
                           camera->GetEyeZPosition() + camera->GetViewZDirection());
    m_shader->SetUniform1f("pointLights[1].ambientIntensity",0.9f);
    m_shader->SetUniform1f("pointLights[1].specularStrength",0.5f);
    m_shader->SetUniform1f("pointLights[1].constant",1.0f);
    m_shader->SetUniform1f("pointLights[1].linear",0.09f);
    m_shader->SetUniform1f("pointLights[1].quadratic",0.032f);
}
