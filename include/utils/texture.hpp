#pragma once

/**
 * @file texture.hpp
 * @brief Texture definition
 */

/// Enumeration for the texture IDs.
enum class Texture
{
    CITY_IDLE,
    CITY_SELECTED,
    CITY_UNBOUGHT,
    ROAD,
    COUNT  // Number of textures.
};

// Number of textures
constexpr int NUM_TEXTURES = static_cast<int>(Texture::COUNT);

/**
 * @brief returns the texture file path
 *
 * @param[in] texture texture id, must be valid
 *
 * @return (const char*) texture fle path
 * 
 */
const char* texture_path(Texture texture);

/**
 * @brief checks if texture is valid
 *
 * @param[in] texture texture id
 *
 * @return bool
 * @retval true  - texture >= 0 && texture < Texture::COUNT
 * @retval false - texture out of range
 */
static constexpr bool is_valid(Texture texture)
{
    return int(texture) >= 0 && int(texture) < NUM_TEXTURES;
}