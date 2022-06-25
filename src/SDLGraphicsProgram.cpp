#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Constants.hpp"
// Include the 'Renderer.hpp' which deteremines what
// the graphics API is going to be for OpenGL
#include "Renderer.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <SkyBox.hpp>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// The window we'll be rendering to
	m_window = NULL;

    m_width = w;
    m_height = h;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
	}
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // We want to request a double buffer for smooth updating.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create window
    m_window = SDL_CreateWindow( "Lab",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            m_width,
                            m_height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

    // Check if Window did not create.
    if( m_window == NULL ){
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    //Create an OpenGL Graphics Context
    m_openGLContext = SDL_GL_CreateContext( m_window );
    if( m_openGLContext == NULL){
        std::cerr << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    // Initialize GLAD Library
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cerr << "Failed to iniitalize GLAD\n";
        exit(EXIT_FAILURE);
    }

    // If initialization succeeds then print out a list of errors in the constructor.
    SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL errors detected during initialization\n\n");

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


//Loops forever!
void SDLGraphicsProgram::SetLoopCallback(std::function<void(void)> callback){
    
    // Create a renderer
    std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(m_width,m_height);    

    // Create our skybox
    std::shared_ptr<SkyBox> sky = std::make_shared<SkyBox>();
    sky->LoadTexture("./assets/textures/skybox/");

    // Create our terrain
    std::shared_ptr<Terrain> myTerrain = std::make_shared<Terrain>(Constants::TERRAIN_BOX_SIZE,"./assets/textures/terrain2.ppm");
    myTerrain->LoadTextures("./assets/textures/grasstexture.ppm");

    std::shared_ptr<SceneNode> skyNode;
    skyNode = std::make_shared<SceneNode>(sky, "./shaders/skyboxVert.glsl", "./shaders/skyboxFrag.glsl");

    // Create a node for our terrain 
    std::shared_ptr<SceneNode> terrainNode;
    terrainNode = std::make_shared<SceneNode>(myTerrain,"./shaders/vert.glsl","./shaders/frag.glsl");

    // Set our SceneTree up
    renderer->setRoot(terrainNode);
    terrainNode->AddChild(skyNode.get());

    // Set a default position for our camera
    float initialEyesYPOS = myTerrain->ComputeHeight(Constants::PLAYER_START_X_POS, Constants::PLAYER_START_Z_POS);
    renderer->GetCamera(0)->SetCameraEyePosition(Constants::PLAYER_START_X_POS,initialEyesYPOS + Constants::EYES_HEIGHT, Constants::PLAYER_START_Z_POS);
  
  
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // Center our mouse
    SDL_WarpMouseInWindow(m_window,m_width/2,m_height/2);

    // Get a pointer to the keyboard state
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);


    // While application is running
    while (!quit) {
        // For our terrain setup the identity transform each frame
        // By default set the terrain node to the identity
        // matrix.
        terrainNode->GetLocalTransform().LoadIdentity();
        // Invoke(i.e. call) the callback function
        callback();

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Handle keyboad input for the camera class
            if (e.type == SDL_MOUSEMOTION) {
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                renderer->GetCamera(0)->MouseLook(mouseX, mouseY);
            }
        } // End SDL_PollEvent loop.

        // Move left or right
        if (keyboardState[SDL_SCANCODE_LEFT]) {
            //renderer->GetCamera(0)->MoveLeft(cameraSpeed);
            float terrainHeight = myTerrain->ComputeHeight(renderer->GetCamera(0)->GetEyeXPosition()
                                                           - renderer->GetCamera(0)->GetViewXDirection() * cameraSpeed,
                                                           renderer->GetCamera(0)->GetEyeZPosition()
                                                           - renderer->GetCamera(0)->GetViewZDirection() * cameraSpeed);
            renderer->GetCamera(0)->WalkLeft(cameraSpeed, terrainHeight);
        }else if(keyboardState[SDL_SCANCODE_RIGHT]){
            //renderer->GetCamera(0)->MoveRight(cameraSpeed);
            float terrainHeight = myTerrain->ComputeHeight(renderer->GetCamera(0)->GetEyeXPosition()
                                                           + renderer->GetCamera(0)->GetViewXDirection() * cameraSpeed,
                                                           renderer->GetCamera(0)->GetEyeZPosition()
                                                           + renderer->GetCamera(0)->GetViewZDirection() * cameraSpeed);
            renderer->GetCamera(0)->WalkRight(cameraSpeed, terrainHeight);
        }

        // Move forward or back
        if (keyboardState[SDL_SCANCODE_UP]) {
            //renderer->GetCamera(0)->MoveForward(cameraSpeed);
            float terrainHeight = myTerrain->ComputeHeight(renderer->GetCamera(0)->GetEyeXPosition()
                    + renderer->GetCamera(0)->GetViewXDirection() * cameraSpeed,
                    renderer->GetCamera(0)->GetEyeZPosition()
                    + renderer->GetCamera(0)->GetViewZDirection() * cameraSpeed);
            renderer->GetCamera(0)->WalkForward(cameraSpeed, terrainHeight);
        }else if(keyboardState[SDL_SCANCODE_DOWN]){
            //renderer->GetCamera(0)->MoveBackward(cameraSpeed);
            float terrainHeight = myTerrain->ComputeHeight(renderer->GetCamera(0)->GetEyeXPosition()
                                                           - renderer->GetCamera(0)->GetViewXDirection() * cameraSpeed,
                                                           renderer->GetCamera(0)->GetEyeZPosition()
                                                           - renderer->GetCamera(0)->GetViewZDirection() * cameraSpeed);
            renderer->GetCamera(0)->WalkBackward(cameraSpeed, terrainHeight);
        }

        // Move up or down
        /*if(keyboardState[SDL_SCANCODE_LSHIFT] || keyboardState[SDL_SCANCODE_RSHIFT])   {
=======
        if(keyboardState[SDL_SCANCODE_LSHIFT] || keyboardState[SDL_SCANCODE_RSHIFT])   {

>>>>>>> 3ca4883... Fix dependency problem
            renderer->GetCamera(0)->MoveUp(cameraSpeed);
        }else if(keyboardState[SDL_SCANCODE_LCTRL] || keyboardState[SDL_SCANCODE_RCTRL]){
            renderer->GetCamera(0)->MoveDown(cameraSpeed);
        }*/

        int TERRAIN_SCALE_CODE = SDL_SCANCODE_0;
        int TERRAIN_PERSISTENCE_CODE = SDL_SCANCODE_1;
        int TERRAIN_OCTAVES_CODE = SDL_SCANCODE_2;
        int TERRAIN_LACUNARITY_CODE = SDL_SCANCODE_3;
        int TERRAIN_EXPONENTIATION_CODE = SDL_SCANCODE_4;
        int TERRAIN_HEIGHT_CODE = SDL_SCANCODE_5;

        bool terrainChanged = false;

        if (keyboardState[TERRAIN_SCALE_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_SCALE += 25;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT] && Constants::TERRAIN_SCALE > 25) {
                Constants::TERRAIN_SCALE -= 25;
                terrainChanged = true;
            }
        }
        else if (keyboardState[TERRAIN_PERSISTENCE_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_PERSISTENCE += 0.1;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT] && Constants::TERRAIN_PERSISTENCE > 0) {
                Constants::TERRAIN_PERSISTENCE -= 0.1;
                terrainChanged = true;
            }
        }
        else if (keyboardState[TERRAIN_OCTAVES_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_OCTAVES += 1;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT] && Constants::TERRAIN_OCTAVES > 1) {
                Constants::TERRAIN_OCTAVES -= 1;
                terrainChanged = true;
            }
        }
        else if (keyboardState[TERRAIN_LACUNARITY_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_LACUNARITY += 0.1;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT]) {
                Constants::TERRAIN_LACUNARITY -= 0.1;
                terrainChanged = true;
            }
        }
        else if (keyboardState[TERRAIN_EXPONENTIATION_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_EXPONENTIATION += 0.25;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT]) {
                Constants::TERRAIN_EXPONENTIATION -= 0.25;
                terrainChanged = true;
            }
        }
        else if (keyboardState[TERRAIN_HEIGHT_CODE]) {
            if (keyboardState[SDL_SCANCODE_RSHIFT]) {
                Constants::TERRAIN_HEIGHT += 50;
                terrainChanged = true;
            }
            if (keyboardState[SDL_SCANCODE_LSHIFT]) {
                Constants::TERRAIN_HEIGHT -= 50;
                terrainChanged = true;
            }
        }

        if (terrainChanged) {
            std::cout << Constants::TERRAIN_OCTAVES << std::endl;
            myTerrain->LoadHeightMap();
            myTerrain->Init();
        }

        std::cout << renderer->GetCamera(0)->GetEyeXPosition() << " " << renderer->GetCamera(0)->GetEyeZPosition() << std::endl;

        // Update the terrain based on the camera location
        myTerrain->MoveCamera(renderer->GetCamera(0)->GetEyeXPosition(), renderer->GetCamera(0)->GetEyeZPosition());

        // Update our scene through our renderer
        renderer->Update();
        // Render our scene using our selected renderer
        renderer->Render();

        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        
        /*std::shared_ptr<Shader> skyboxShader = std::make_shared<Shader>();

        // Create shader
        skyboxShader = std::make_shared<Shader>();
        // Setup shaders for the node.
        std::string vertexShader = skyboxShader->LoadShader(vertShader);
        std::string fragmentShader = skyboxShader->LoadShader(fragShader);

        // Actually create our shader
        m_shader->CreateShader(vertexShader, fragmentShader);

        skyboxShader->Bind();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);*/

        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
