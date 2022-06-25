#include "SkyBox.hpp"
#include "Constants.hpp"
#include "Image.hpp"
#include "Camera.hpp"
#include "Transform.hpp"
#include "Shader.hpp"

#include <iostream>
#include <math.h>
#include <PerlinNoise/PerlinNoise.hpp>
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

    //*m_geometry.AddVertex(-1.0f, -1.0f, 1.0f);
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

    /*float skyboxVertices[] = {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);*/

    m_geometry.AddVertex(-1.0f * BOX_SIZE, -1.0f * BOX_SIZE, 1.0f * BOX_SIZE);
    m_geometry.AddVertex(1.0f * BOX_SIZE, -1.0f * BOX_SIZE, 1.0f * BOX_SIZE);
    m_geometry.AddVertex(1.0f * BOX_SIZE, -1.0f * BOX_SIZE, -1.0f * BOX_SIZE);
    m_geometry.AddVertex(-1.0f * BOX_SIZE, -1.0f * BOX_SIZE, -1.0f * BOX_SIZE);
    m_geometry.AddVertex(-1.0f * BOX_SIZE, 1.0f * BOX_SIZE, 1.0f * BOX_SIZE);
    m_geometry.AddVertex(1.0f * BOX_SIZE, 1.0f * BOX_SIZE, 1.0f * BOX_SIZE);
    m_geometry.AddVertex(1.0f * BOX_SIZE, 1.0f * BOX_SIZE, -1.0f * BOX_SIZE);
    m_geometry.AddVertex(-1.0f * BOX_SIZE, 1.0f * BOX_SIZE, -1.0f * BOX_SIZE);

    // Right Image
    m_geometry.AddIndex(1);
    m_geometry.AddIndex(2);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(5);
    m_geometry.AddIndex(1);

    //Left Image
    m_geometry.AddIndex(0);
    m_geometry.AddIndex(4);
    m_geometry.AddIndex(7);
    m_geometry.AddIndex(7);
    m_geometry.AddIndex(3);
    m_geometry.AddIndex(0);

    // Top Image
    m_geometry.AddIndex(4);
    m_geometry.AddIndex(5);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(7);
    m_geometry.AddIndex(4);

    // Botttom Image
    m_geometry.AddIndex(0);
    m_geometry.AddIndex(3);
    m_geometry.AddIndex(2);
    m_geometry.AddIndex(2);
    m_geometry.AddIndex(1);
    m_geometry.AddIndex(0);

    // Front Image
    m_geometry.AddIndex(0);
    m_geometry.AddIndex(1);
    m_geometry.AddIndex(5);
    m_geometry.AddIndex(5);
    m_geometry.AddIndex(4);
    m_geometry.AddIndex(0);

    // Back Image
    m_geometry.AddIndex(3);
    m_geometry.AddIndex(7);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(6);
    m_geometry.AddIndex(2);
    m_geometry.AddIndex(3);

    m_geometry.GenVertices();

    m_vertexBufferLayout.CreatePositionBufferLayout(m_geometry.GetBufferDataSize(),
                                                    m_geometry.GetIndicesSize(),
                                                    m_geometry.GetBufferDataPtr(),
                                                    m_geometry.GetIndicesDataPtr());

}

// Destructor
SkyBox::~SkyBox(){
    // Delete our allocatted heightmap data
    /*if(m_heightData!=nullptr){
        delete m_heightData;
    }*/
}

void SkyBox::LoadTexture(std::string fileName) {
    m_textureDiffuse.LoadSkyBoxTexture(fileName);
}

void SkyBox::UpdateShader(Shader* m_shader, glm::mat4 projectionMatrix, Camera* camera, Transform m_worldTransform) {
    std::cout << "Updating Sky Box" << std::endl;
    m_shader->Bind();
    m_shader->SetUniform1i("skybox", 0);
    //glm::mat3 temp_mat3;
    //glm::glm_mat4_pick3(camera->GetWorldToViewmatrix(), temp_mat3);
    m_shader->SetUniformMatrix4fv("view", &glm::mat4(glm::mat3(camera->GetWorldToViewmatrix()))[0][0]);
    //m_shader->SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
    m_shader->SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);
}

void SkyBox::Render() {
    std::cout << "I'm rendering in Sky Box" << std::endl;
    Bind();
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureDiffuse.GetID());
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}




/*void SkyBox::MakeTexturedQuad(std::string fileName) {
    uint8_t fileExtensionStart = fileName.find(".");
    if (fileExtensionStart) {
        fileName = fileName.substr(0, fileExtensionStart);
    }

    std::vector<std::string> faces;
    faces.push_back(fileName + "right.ppm");
    faces.push_back(fileName + "left.ppm");
    faces.push_back(fileName + "top.ppm");
    faces.push_back(fileName + "back.ppm");
    faces.push_back(fileName + "front.ppm");
    faces.push_back(fileName + "back.ppm");


    LoadSkyBox(faces);
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

    texturedID = textureID;
}*/