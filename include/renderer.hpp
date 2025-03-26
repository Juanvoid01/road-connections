#pragma once
/**
 * @file renderer.hpp
 *
 * @brief Renderer declarations
 *
 */
#include <SDL2/SDL.h>
#include "object_circle.hpp"

/**
 * @brief Renderer
 *
 * Renderer class
 *
 */
class Renderer
{
public:
    Renderer() = delete;
    Renderer(const char *title, int w, int h);
    ~Renderer();

    void draw(const ObjectCircleList circles);

    // Texture loading helper
    SDL_Texture *load_texture(const char *path);

    void clear();
    void present();

    inline bool initialize_succesfully() const { return window && sdl_renderer; }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *sdl_renderer = nullptr;

    void draw(const ObjectCircle& circle);
};