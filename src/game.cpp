#include <cstdio>
#include <memory>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "game.h"
#include "texture.h"

Game::Game(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    paused = false;
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        curTime = SDL_GetPerformanceCounter();

        //Main loop flag
        bool quit = false;

        //While application is running
        while( !quit )
        {
            if (!update()) {
                quit = true;
            }

            //Render
            render();
        }
    }

    //Free resources and close SDL
    close();

}

bool Game::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);

        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

        //Create window
        gWindow = SDL_CreateWindow( "Bengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( gWindow == nullptr )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if( gContext == nullptr )
            {
                printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if( glewError != GLEW_OK )
                {
                    printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
                }

                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 )
                {
                    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                }

                //Initialize OpenGL
                initGL();
            }
        }
    }

    return success;
}

void Game::initGL()
{
    // Load textures
    std::shared_ptr<Texture> stone = std::make_shared<Texture>("../textures/stone.png");
    std::shared_ptr<Texture> wool = std::make_shared<Texture>("../textures/wool.png");
    std::shared_ptr<Texture> shroom = std::make_shared<Texture>("../textures/shroom.png");

    renderer = std::make_unique<Renderer>();
    gameCamera = std::make_shared<Camera>(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 3.0f));
    renderer->setCamera(gameCamera);

    object = std::make_shared<Object>(stone, glm::vec3(0, 1, 0));
    object2 = std::make_shared<Object>(wool, glm::vec3(2, 0, 0));
    object3 = std::make_shared<Object>(shroom, glm::vec3(-2, .5f, 0));

    gameShader = std::make_shared<Shader>("../shaders/vertex.shader", "../shaders/frag.shader");
    renderer->setShader(gameShader);
    gameShader->setInt("texture0", 0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL initialization error: " << err << std::endl;
    }

}

bool Game::update()
{
    Uint64 lastTime = curTime;
    curTime = SDL_GetPerformanceCounter();

    double dt = ((double)(curTime - lastTime) / (double)SDL_GetPerformanceFrequency());

    //Event handler
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 )
    {
        //User requests quit
        if( e.type == SDL_QUIT ) {
            return false;
        }
        if ( e.type == SDL_KEYDOWN ) {
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                paused = !paused;
                if (paused) {
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                } else {
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                }
            }
        }
        if (!paused) {
            if ( e.type == SDL_MOUSEMOTION) {
                gameCamera->processMouse(e.motion.xrel, e.motion.yrel);
            }
        }
    }

    if (paused) { // Return early so we don't do any of the update code
        return true;
    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState( nullptr );
    float forward = 0;
    float right = 0;
    if (currentKeyStates[SDL_SCANCODE_W]) {
        forward += 1;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        forward -= 1;
    }
    if (currentKeyStates[SDL_SCANCODE_D]) {
        right += 1;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        right -= 1;
    }
    // TODO don't hard code dt
    gameCamera->processMovement((float)dt, forward, right);

    // rotate cube
    float time = (float)SDL_GetTicks() / 1000.0f;
    glm::mat4 rot = glm::mat4(1.0f);
    rot = glm::rotate(rot, time, glm::vec3(1, 1, 0));
    object->setRot(rot);
    object2->setY(sin(time));
    object3->setScale(cos(time) + 1);

    return true;
}

void Game::render()
{
    renderer->startDraw();
    renderer->draw(object);
    renderer->draw(object2);
    renderer->draw(object3);

    //Update screen
    SDL_GL_SwapWindow( gWindow );
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Game::close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
}

