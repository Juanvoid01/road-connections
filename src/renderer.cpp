/**
 * @file renderer.cpp
 *
 * @brief Renderer implementation
 *
 */
#include "renderer.hpp"
#include <iostream>

Renderer::Renderer(const char *title, int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!sdlRenderer)
    {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
// Draw an object (automatically chooses texture or color)
void Renderer::draw(const Object &object)
{
    /*SDL_Rect destRect = {
        static_cast<int>(object.x),
        static_cast<int>(object.y),
        object.width,
        object.height};

    if (object.texture)
    {
        // Draw texture
        SDL_RenderCopy(sdlRenderer, object.texture, nullptr, &destRect);
    }
    else
    {
        // Draw filled color
        SDL_SetRenderDrawColor(sdlRenderer, object.fillColor.r, object.fillColor.g, object.fillColor.b, object.fillColor.a);
        SDL_RenderFillRect(sdlRenderer, &destRect);
    }*/
}

// Texture loading helper
SDL_Texture *Renderer::load_texture(const char *path)
{
    SDL_Surface *surface = SDL_LoadBMP(path); // For PNGs use SDL_image
    SDL_Texture *tex = SDL_CreateTextureFromSurface(sdlRenderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

void Renderer::clear()
{
    // Set clear color to black (or your preferred background)
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); // RGBA: black
    SDL_RenderClear(sdlRenderer);
}

void Renderer::present() { SDL_RenderPresent(sdlRenderer); }
