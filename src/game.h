#ifndef CUBELANDS_GAME_H
#define CUBELANDS_GAME_H

#include <memory>
#include <SDL.h>
#include <GL/glew.h>
#include "shader.h"
#include "texture.h"
#include "camera.h"
#include "object.h"
#include "renderer.h"

class Game {
public:
    /**
     * Creates a game with a given screen width and height
     * @param width
     * @param height
     */
    Game(int width, int height);

private:
    /**
     * Starts up SDL, creates window, and initializes OpenGL
     * @return whether the initialization was successful
     */
    bool init();

    /**
     * Initializes rendering program
     */
    void initGL();

    /**
     * Updates the game based on new inputs and past state
     * @return whether the update was successful
     */
    bool update();

    /**
     * Renders game content to the screen
     */
    void render();

    /**
     * Frees media and shuts down SDL
     */
    void close();

    // The window rendered to
    SDL_Window* gWindow = nullptr;

    // OpenGL context
    SDL_GLContext gContext;

    // Shader
    std::shared_ptr<Shader> gameShader;

    std::unique_ptr<Renderer> renderer;

    int screenWidth;

    int screenHeight;

    std::shared_ptr<Camera> gameCamera;

    std::shared_ptr<Object> object;

    std::shared_ptr<Object> object2;

    std::shared_ptr<Object> object3;
};

#endif //CUBELANDS_GAME_H
