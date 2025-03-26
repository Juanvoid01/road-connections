#pragma once
/**
 * @file renderer.hpp
 *
 * @brief Renderer declarations
 *
 */
#include <SDL2/SDL.h>
#include "object.hpp"

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

    void draw(const Object &object);
    // Texture loading helper
    SDL_Texture *load_texture(const char *path);

    void clear();
    void present();

    inline bool initialize_succesfully() const { return window && sdlRenderer; }

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *sdlRenderer = nullptr;
};