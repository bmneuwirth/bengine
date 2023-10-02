#include <cstdio>
#include <memory>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "game.h"
#include "texture.h"

Game::Game(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    paused = false;
    fullscreen = false;
    //Start up SDL and create window
    if( !init() ) {
        printf( "Failed to initialize!\n" );
    }
    else {
        curTime = SDL_GetPerformanceCounter();

        //Main loop flag
        bool quit = false;

        //While application is running
        while( !quit ) {
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

bool Game::init() {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);
    renderer = std::make_unique<Renderer>(screenWidth, screenHeight);

    // Load textures
    std::shared_ptr<Texture> stone = std::make_shared<Texture>("../textures/stone.png");
    std::shared_ptr<Texture> wool = std::make_shared<Texture>("../textures/wool.png");
    std::shared_ptr<Texture> shroom = std::make_shared<Texture>("../textures/shroom.png");

    gameCamera = std::make_shared<Camera>(screenWidth, screenHeight, glm::vec3(0.0f, 0.0f, 3.0f));
    renderer->setCamera(gameCamera);

    object = std::make_shared<Object>(stone, glm::vec3(0, 1, 0));
    object2 = std::make_shared<Object>(wool, glm::vec3(2, 0, 0));
    object3 = std::make_shared<Object>(shroom, glm::vec3(-2, .5f, 0));

    gameShader = std::make_shared<Shader>("../shaders/vertex.shader", "../shaders/frag.shader");
    renderer->setShader(gameShader);
    gameShader->setInt("texture0", 0);

    return true;
}

bool Game::update() {
    Uint64 lastTime = curTime;
    curTime = SDL_GetPerformanceCounter();

    double dt = ((double)(curTime - lastTime) / (double)SDL_GetPerformanceFrequency());

    //Event handler
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 ) {
        //User requests quit
        if( e.type == SDL_QUIT ) {
            return false;
        }
        if ( e.type == SDL_KEYDOWN ) {
            if (e.key.keysym.sym == SDLK_f) {
                fullscreen = !fullscreen;
            }
            else if (e.key.keysym.sym == SDLK_ESCAPE) {
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

void Game::render() {
    renderer->startDraw();
    renderer->draw(object);
    renderer->draw(object2);
    renderer->draw(object3);
    renderer->endDraw();
}

void Game::close() {
    renderer.reset();

    //Quit SDL subsystems
    SDL_Quit();
}

