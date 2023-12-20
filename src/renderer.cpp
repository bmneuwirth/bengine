//
// Created by Ben Neuwirth on 9/30/23.
//

#include "renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <utility>

Renderer::Renderer(int screenWidth, int screenHeight) {
    curShader = nullptr;
    camera = nullptr;
    isFullscreen = false;

    // Assume single display for now. We'll deal with multi-monitor stuff later.
    SDL_GetCurrentDisplayMode(0, &fullscreenMode);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //Create window
    windowedMode.w = screenWidth;
    windowedMode.h = screenHeight;
    windowedMode.refresh_rate = fullscreenMode.refresh_rate;
    windowedMode.format = fullscreenMode.format;
    windowedMode.driverdata = fullscreenMode.driverdata;

    window = SDL_CreateWindow( "Bengine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    SDL_SetWindowDisplayMode(window, &windowedMode);
    context = SDL_GL_CreateContext( window );

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

    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position attribute
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

Renderer::~Renderer() {
    SDL_DestroyWindow( window );
    window = nullptr;
}

void Renderer::startDraw() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    curShader->setMat4("view", glm::value_ptr(camera->getViewMatrix()));
}

void Renderer::draw(const std::shared_ptr<Object>& obj) {
    curShader->setMat4("model", glm::value_ptr(obj->getModel()));
    obj->getTexture()->bind();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, obj->getVBO());
    // TODO Move this
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glDrawArrays(GL_TRIANGLES, 0, obj->getVertCount());
}

void Renderer::endDraw() {
    //Update screen
    SDL_GL_SwapWindow( window );
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::setCamera(std::shared_ptr<Camera> cam) {
    camera = std::move(cam);
    if (curShader != nullptr) {
        curShader->setMat4("projection", glm::value_ptr(camera->getProjMatrix()));
    }
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    curShader = std::move(shader);
    curShader->use();
    curShader->setMat4("projection", glm::value_ptr(camera->getProjMatrix()));
}

void Renderer::toggleFullscreen() {
    isFullscreen = !isFullscreen;
    if (isFullscreen) {
        SDL_SetWindowDisplayMode(window, &fullscreenMode);
        camera->resize(fullscreenMode.w, fullscreenMode.h);
    }
    else {
        SDL_SetWindowDisplayMode(window, &windowedMode);
        camera->resize(windowedMode.w, windowedMode.h);
    }
    SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
    curShader->setMat4("projection", glm::value_ptr(camera->getProjMatrix()));
}