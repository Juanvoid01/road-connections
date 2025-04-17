#pragma once
/**
 * @file renderer.hpp
 *
 * @brief Renderer declarations
 *
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    Renderer(const char* title, int w, int h);
    ~Renderer();

    void clear();
    void draw();
    void present();

    void get_window_size(int& width, int& height) const;

    inline bool initialize_succesfully() const { return window && sdl_renderer; }

   private:
    SDL_Window* window = nullptr;
    SDL_Renderer* sdl_renderer = nullptr;
};