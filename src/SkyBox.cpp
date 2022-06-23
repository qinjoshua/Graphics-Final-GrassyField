#include "SkyBox.hpp"
#include "Constants.hpp"
#include "Image.hpp"

#include <iostream>
#include <math.h>
#include <PerlinNoise/PerlinNoise.hpp>

// Constructor for our object
// Calls the initialization method
SkyBox::SkyBox(std::string fileName) {
    std::cout << "(SkyBox.cpp) Constructor called \n";

    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);

    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);

    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);

    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);

    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);

    m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    m_geometry.AddVertex(1.0f, -1.0f, 1.0f);

    
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

    // Initialize the SkyBox
    Init();
}

// Destructor
SkyBox::~SkyBox(){
    // Delete our allocatted heightmap data
    if(m_heightData!=nullptr){
        delete m_heightData;
    }
}


// Creates a grid of segments
// This article has a pretty handy illustration here:
// http://www.learnopengles.com/wordpress/wp-content/uploads/2012/05/vbo.png
// of what we are trying to do.
void SkyBox::Init(){
    
}

void SkyBox::LoadTexture(std::string filepath){ 
    m_textureDiffuse.LoadTexture(filepath); // Found in object
}

// Code inspired by this handy demonstration:
// https://www.youtube.com/watch?v=U9q-jM3-Phc&t=9s&ab_channel=SimonDev
void SkyBox::LoadSkyBox(std::vector<std::string> faces) {
    unsigned int textureID;/*
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        Image* m_image = new Image(faces[i].c_str());
        m_image->LoadPPM(true);
        
        if (m_image)
        {
            glTexImage2D(GL_TEXTURE_2D,
                0,
                GL_RGB,
                m_image->GetWidth(),
                m_image->GetHeight(),
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                m_image->GetPixelDataPtr());
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/
}