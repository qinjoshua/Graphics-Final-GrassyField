#include "..\include\SkyBox.hpp"
#include "SkyBox.hpp"
#include "Constants.hpp"
#include "Image.hpp"

#include <iostream>
#include <math.h>
#include <PerlinNoise/PerlinNoise.hpp>

// Constructor for our object
// Calls the initialization method
SkyBox::SkyBox() {
    std::cout << "(SkyBox.cpp) Constructor called \n";

    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);

    //m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);

    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);

    ///*m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);*/

    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, 1.0f);
    //m_geometry.AddVertex(-1.0f, 1.0f, -1.0f);

    //m_geometry.AddVertex(-1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, -1.0f);
    //m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
    //m_geometry.AddVertex(1.0f, -1.0f, 1.0f);


    //m_geometry.GenVertices();

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

// Destructor
SkyBox::~SkyBox(){
    // Delete our allocatted heightmap data
    /*if(m_heightData!=nullptr){
        delete m_heightData;
    }*/
}

void SkyBox::MakeTexturedQuad(std::string fileName) {
    uint8_t fileExtensionStart = fileName.find(".");
    if (fileExtensionStart) {
        fileName = fileName.substr(0, fileExtensionStart);
    }

    std::vector<std::string> faces;
    faces.push_back(fileName + "right.ppm");
    faces.push_back(fileName + "left.ppm");
    faces.push_back(fileName + "top.ppm");
    faces.push_back(fileName + "front.ppm");
    faces.push_back(fileName + "back.ppm");

    LoadSkyBox(faces);
}

void SkyBox::Render() {
    
}

// Code inspired by this article:
// https://learnopengl.com/Advanced-OpenGL/Cubemaps
void SkyBox::LoadSkyBox(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned int index = i >= GL_TEXTURE_CUBE_MAP_NEGATIVE_Y ? i : i + 1;

        Image* image = new Image(faces[i].c_str());
        image->LoadPPM(true);
        
        if (image)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
                0, GL_RGB, image->GetWidth(), image->GetHeight(), 0,
                GL_RGB, GL_UNSIGNED_BYTE, image->GetPixelDataPtr());
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
        }

        // Delete our image
        if (image != nullptr) {
            delete image;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}