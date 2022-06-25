#include "Object.hpp"
#include "Camera.hpp"
#include "Error.hpp"
#include "Transform.hpp"
#include "Shader.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"


Object::Object(){
}

Object::~Object(){
    
}

// TODO: In the future it may be good to 
// think about loading a 'default' texture
// if the user forgets to do this action!
void Object::LoadTexture(std::string fileName){
        // Load our actual textures
        m_textureDiffuse.LoadTexture(fileName);
    //m_textureDiffuse.LoadSkyBoxTexture(fileName);
}

// Initialization of object as a 'quad'
//
// This could be called in the constructor or
// otherwise 'explicitly' called this
// so we create our objects at the correct time
void Object::MakeTexturedQuad(std::string fileName){

        // Setup geometry
        // We are using a new abstraction which allows us
        // to create triangles shapes on the fly
        // Position and Texture coordinate 
        m_geometry.AddVertex(-1.0f,-1.0f, 0.0f, 0.0f, 0.0f);
        m_geometry.AddVertex( 1.0f,-1.0f, 0.0f, 1.0f, 0.0f);
    	m_geometry.AddVertex( 1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
        m_geometry.AddVertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
            
        // Make our triangles and populate our
        // indices data structure	
        m_geometry.MakeTriangle(0,1,2);
        m_geometry.MakeTriangle(2,3,0);

        // This is a helper function to generate all of the geometry
        m_geometry.Gen();

        // Create a buffer and set the stride of information
        // NOTE: How we are leveraging our data structure in order to very cleanly
        //       get information into and out of our data structure.
        m_vertexBufferLayout.CreateNormalBufferLayout(m_geometry.GetBufferDataSize(),
                                        m_geometry.GetIndicesSize(),
                                        m_geometry.GetBufferDataPtr(),
                                        m_geometry.GetIndicesDataPtr());

        // Load our actual texture
        // We are using the input parameter as our texture to load
        m_textureDiffuse.LoadTexture(fileName.c_str());
}

// Bind everything we need in our object
// Generally this is called in update() and render()
// before we do any actual work with our object
void Object::Bind(){
        // Make sure we are updating the correct 'buffers'
        m_vertexBufferLayout.Bind();
        // Diffuse map is 0 by default, but it is good to set it explicitly
        m_textureDiffuse.Bind(0);
        // Detail map
//        m_detailMap.Bind(1); // NOTE: Not yet supported
}

// Render our geometry
void Object::Render(){
    // Call our helper function to just bind everything
    Bind();
	//Render data
    glDrawElements(GL_TRIANGLES,
                   m_geometry.GetIndicesSize(), // The number of indicies, not triangles.
                   GL_UNSIGNED_INT,             // Make sure the data type matches
                        nullptr);               // Offset pointer to the data. 
                                                // nullptr because we are currently bound*
}

void Object::UpdateShader(Shader* m_shader, glm::mat4 projectionMatrix, Camera* camera, Transform m_worldTransform) {
    std::cout << "I am updating in Sky Box" << std::endl;
    /*// For our object, we apply the texture in the following way
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
    m_shader->SetUniform1f("pointLights[1].quadratic",0.032f);*/


    /*m_shader->Bind();
    m_shader->SetUniformMatrix4fv("skybox", 0);
    m_shader->SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
    m_shader->SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);*/
}

