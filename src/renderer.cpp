/**
 * @file renderer.cpp
 *
 * @brief Renderer implementation
 *
 */
#include "renderer.hpp"
#include "game_controller.hpp"
#include "texture_manager.hpp"
#include <iostream>

Renderer::Renderer(const char* title, int w, int h)
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

    IMG_Init(IMG_INIT_PNG);  // Supports PNG files

    TextureManager::init(sdl_renderer);
}

Renderer::~Renderer()
{
    TextureManager::clean();
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::clear()
{
    // Set clear color to black (or your preferred background)
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);  // RGBA: black
    SDL_RenderClear(sdl_renderer);
}

void Renderer::present()
{
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::draw()
{
    const CitiesList& cities = GameController::get_cities();
    const Camera& camera = GameController::get_camera();
    for (const City& city : cities)
    {
        SDL_Texture* texture_pointer = TextureManager::get_pointer(city.texture());
        SDL_Rect rect = hitboxRect_to_SDL_Rect(city.hitbox());
        rect.x = static_cast<int>((rect.x - camera.position().x) * camera.zoom());
        rect.y = static_cast<int>((rect.y - camera.position().y) * camera.zoom());
        rect.w *= camera.zoom();
        rect.h *= camera.zoom();

        SDL_RenderCopy(sdl_renderer, texture_pointer, NULL, &rect);  // render texture
    }

    const RoadList& roads = GameController::get_roads();

    for (const Road& road : roads)
    {
        /*if (road.state() != Road::State::BUILT)
        {
            continue;
        }
        const Vector2F p = road.i
        // compute delta & length
        float dx = x2 - x1, dy = y2 - y1;
        float length = sqrtf(dx * dx + dy * dy);
        float angle = atan2f(dy, dx) * (180.0f / M_PI);

        // destination rect (floating)
        SDL_FRect dst;
        dst.x = x1;
        dst.y = y1 - thickness * 0.5f;  // center the road on the line
        dst.w = length;
        dst.h = thickness;

        // render rotated
        SDL_RenderCopyExF(ren, white_tex, nullptr, &dst, angle,
                          nullptr,  // rotate around dst’s top‑left (already adjusted)
                          SDL_FLIP_NONE);*/
    }
}


void Renderer::get_window_size(int& width, int& height) const
{
    SDL_assert(window);
    SDL_GetWindowSize(window, &width, &height);
}