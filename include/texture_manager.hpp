#pragma once

/**
 * @file texture_manager.hpp
 * @brief Texture manager subsystem
 */

#include <SDL2/SDL.h>

#include "texture.hpp"

namespace TextureManager
{
    /**
     * @brief Initialize the texture manager loading all textures.
     *
     * @param[in] renderer pointer to renderer
     *
     */
    void init(SDL_Renderer* renderer);

    /**
     * @brief Retrieve a the pointer to the Texture data
     *
     * @param texture The texture identifier.
     * @return SDL_Texture* Pointer to the loaded texture data.
     */
    SDL_Texture* get_pointer(Texture texture);

    /**
     * @brief Clean up all the Texture manager and all the loaded textures.
     */
    void clean();

};  // namespace TextureManager