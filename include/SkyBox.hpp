/** @file SkyBox.hpp
 *  @brief Create a SkyBox
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Object.hpp"

#include <vector>
#include <string>

class SkyBox : public Object {
public:
    // Takes in file names for the faces of the SkyBox.
    SkyBox (std::string fileName);
    // Destructor
    ~SkyBox ();
    // override the initilization routine.
    void Init();

private:
    // data
    unsigned int m_xSegments;
    unsigned int m_zSegments;

    // Store the height in a multidimensional array
    float* m_heightData;

    // Computes the height of a given x and y coordinate
    float ComputeHeight(int x, int y);
    // Load textures
    void LoadTexture(std::string filepath);
    // Load SkyBox
    void LoadSkyBox(std::vector<std::string> faces);
};

#endif
