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

    sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!sdl_renderer)
    {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Renderer::draw(const ObjectCircleList circles)
{
    int num_circles = circles.size();
    for (int i = 0; i < num_circles; i++)
    {
        draw(circles.get(i));
    }
}

// Texture loading helper
SDL_Texture *Renderer::load_texture(const char *path)
{
    SDL_Surface *surface = SDL_LoadBMP(path); // For PNGs use SDL_image
    SDL_Texture *tex = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    SDL_FreeSurface(surface);
    return tex;
}

void Renderer::clear()
{
    // Set clear color to black (or your preferred background)
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255); // RGBA: black
    SDL_RenderClear(sdl_renderer);
}

void Renderer::present() { SDL_RenderPresent(sdl_renderer); }

// Helper function to draw a circle using the midpoint circle algorithm.
void Renderer::draw(const ObjectCircle& circle)
{
    const SDL_Color color = circle.color;
    const float radius = circle.radius;
    const float center_x = circle.center_x;
    const float center_y = circle.center_y;
    int offsetX = 0;
    int offsetY = radius;
    int d = radius - 1;

    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);

    while (offsetY >= offsetX)
    {
        // Draw the eight symmetric points
        SDL_RenderDrawPoint(sdl_renderer, center_x + offsetX, center_y + offsetY);
        SDL_RenderDrawPoint(sdl_renderer, center_x + offsetY, center_y + offsetX);
        SDL_RenderDrawPoint(sdl_renderer, center_x - offsetX, center_y + offsetY);
        SDL_RenderDrawPoint(sdl_renderer, center_x - offsetY, center_y + offsetX);
        SDL_RenderDrawPoint(sdl_renderer, center_x + offsetX, center_y - offsetY);
        SDL_RenderDrawPoint(sdl_renderer, center_x + offsetY, center_y - offsetX);
        SDL_RenderDrawPoint(sdl_renderer, center_x - offsetX, center_y - offsetY);
        SDL_RenderDrawPoint(sdl_renderer, center_x - offsetY, center_y - offsetX);

        if (d >= 2 * offsetX)
        {
            d -= 2 * offsetX + 1;
            offsetX++;
        }
        else if (d < 2 * (radius - offsetY))
        {
            d += 2 * offsetY - 1;
            offsetY--;
        }
        else
        {
            d += 2 * (offsetY - offsetX - 1);
            offsetY--;
            offsetX++;
        }
    }
}