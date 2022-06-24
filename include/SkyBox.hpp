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
    SkyBox ();
    // Destructor
    ~SkyBox ();
    void MakeTexturedQuad(std::string fileName);
    // override the initilization routine.
    void Init();
    void Render();

private:
    // Load SkyBox
    void LoadSkyBox(std::vector<std::string> faces);
    unsigned int texturedID;
};

#endif
