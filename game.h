#ifndef CUBELANDS_GAME_H
#define CUBELANDS_GAME_H

#include <memory>
#include <SDL.h>
#include <GL/glew.h>
#include "shader.h"

class Game {
public:
    Game(int width, int height);

private:
    //Starts up SDL, creates window, and initializes OpenGL
    bool init();

    //Initializes rendering program and clear color
    bool initGL();

    //Input handler
    void handleKeys( unsigned char key, int x, int y );

    //Per frame update
    void update();

    //Renders quad to the screen
    void render();

    //Frees media and shuts down SDL
    void close();

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //OpenGL context
    SDL_GLContext gContext;

    std::unique_ptr<Shader> gameShader;

    //Render flag
    bool gRenderQuad = true;

    // VAO
    GLuint VAO;

    int screenWidth;

    int screenHeight;
};

#endif //CUBELANDS_GAME_H
