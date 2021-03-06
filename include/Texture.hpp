/** @file Texture.hpp
 *  @brief Loads an image and creates an OpenGL texture on the GPU..
 *  
 *  More...
 *
 *  @author Mike
 *  @bug No known bugs.
 */
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Image.hpp"

#include <glad/glad.h>
#include <string>

class Texture{
public:
    // Constructor
    Texture();
    // Destructor
    ~Texture();
	// Loads and sets up an actual texture
    void LoadTexture(const std::string filepath);
    void LoadSkyBoxTexture(const std::string filepath);

    void SetTile(bool tilingOn);
	// slot tells us which slot we want to bind to.
    // We can have multiple slots. By default, we
    // will set our slot to 0 if it is not specified.
    void Bind(unsigned int slot=0) const;
    // Be done with our texture
    void Unbind();
    GLuint GetID(){ return m_textureID;};
private:
    // Store a unique ID for the texture
    GLuint m_textureID;
	// Filepath to the image loaded
    std::string m_filepath;
    // Store whatever image data inside of our texture class.
    Image* m_image;
    // Store whether or not the texture should tile or stretch
    bool tile;
};



#endif