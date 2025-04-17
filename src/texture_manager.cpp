/**
 * @file texture_manager.cpp
 * @brief Texture manager subsystem
 */

#include "texture_manager.hpp"
#include <SDL_image.h>
#include <array>
#include <stdexcept>
#include <string>

// Array with pointers to textures, indexed via TEXTURE id
static std::array<SDL_Texture*, NUM_TEXTURES> texture_pointers = {nullptr};

/**
 * @brief Initialize the texture manager loading all textures.
 *
 * @param[in] renderer pointer to renderer
 *
 */
void TextureManager::init(SDL_Renderer* renderer)
{
    SDL_assert(renderer);

    for (int texture = 0; texture < NUM_TEXTURES; texture++)
    {
        SDL_assert(texture_pointers[texture] == nullptr && "Texture manager reinitialized without calling clean");
        const char* texture_file = texture_path(static_cast<Texture>(texture));
        texture_pointers[texture] = IMG_LoadTexture(renderer, texture_file);
        if (texture_pointers[texture] == nullptr)
        {
            throw std::runtime_error("Load texture error" + std::string(texture_file));
        }
    }
}

/**
 * @brief Retrieve a the pointer to the Texture data
 *
 * @param texture The texture identifier.
 * @return (SDL_Texture*) texture_pointers[texture].
 */
SDL_Texture* TextureManager::get_pointer(Texture texture)
{
    SDL_assert(is_valid(texture));

    return texture_pointers[static_cast<int>(texture)];
}

/**
 * @brief Clean up all the Texture manager and all the loaded textures.
 */
void TextureManager::clean()
{
    for (int texture = 0; texture < NUM_TEXTURES; texture++)
    {
        if (texture)
        {
            SDL_DestroyTexture(texture_pointers[static_cast<int>(texture)]);
            texture_pointers[static_cast<int>(texture)] = nullptr;
        }
    }
}