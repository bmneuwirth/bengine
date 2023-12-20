//
// Created by Ben Neuwirth on 9/30/23.
//

#ifndef CUBELANDS_RENDERER_H
#define CUBELANDS_RENDERER_H

#include <memory>
#include <SDL.h>
#include <GL/glew.h>
#include "object.h"
#include "camera.h"
#include "shader.h"

/**
 * A class encapsulating the SDL window handling and OpenGL rendering for the game.
 */
class Renderer {
public:
    /**
     * Construct a renderer for a given window size
     * @param screenWidth the width of the window to create
     * @param screenHeight the height of the window to create
     */
    Renderer(int screenWidth, int screenHeight);
    /**
     * Properly deletes the renderer, destroying the SDL window
     */
    ~Renderer();
    Renderer(const Renderer& other) = delete;
    Renderer& operator=(const Renderer& other) = delete;

    /**
     * Starts the draw process for a given frame.
     * Should be called before drawing each frame.
     *
     * Precondition: A shader and camera must be set before drawing.
     */
    void startDraw();

    /**
     * Draws a given object to the screen.
     * @param obj the object being drawn
     */
    void draw(const std::shared_ptr<Object>& obj);

    /**
     * Ends the draw process for a given frame.
     * Should be called after drawing each frame.
     */
    void endDraw();

    /**
     * Set the camera currently being used by the renderer.
     * @param cam the camera to use
     */
    void setCamera(std::shared_ptr<Camera> cam);

    /**
     * Sets the shader currently being used by the renderer.
     * @param shader the shader to use
     */
    void setShader(std::shared_ptr<Shader> shader);

    /**
    * Toggles whether the game should be in fullscreen.
    */
    void toggleFullscreen();

private:
    // The window rendered to
    SDL_Window* window = nullptr;

    // OpenGL context
    SDL_GLContext context;

    GLuint VAO;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Shader> curShader;

    bool isFullscreen;
    SDL_DisplayMode fullscreenMode;
    SDL_DisplayMode windowedMode;
};


#endif //CUBELANDS_RENDERER_H
