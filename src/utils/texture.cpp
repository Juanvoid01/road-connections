/**
 * @file texture.cpp
 * @brief Texture definition
 */

#include "texture.hpp"
#include <SDL_assert.h>
#include <array>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

// find the texture folder path
static const fs::path find_textures_path();

// texture folder path
static const fs::path TEXTURES_PATH = find_textures_path();

// clang-format off
// Array with path files of textures, indexed via TEXTURE id
static const std::string TEXTURE_FILES[NUM_TEXTURES] = {
    fs::path(TEXTURES_PATH / "city_idle.png").string(),
    fs::path(TEXTURES_PATH / "city_selected.png").string(),
    fs::path(TEXTURES_PATH / "city_unbought.png").string(),
    fs::path(TEXTURES_PATH / "road.png").string()
};
// clang-format on

/**
 * @brief returns the texture file path
 *
 * @param[in] texture texture id, must be valid
 *
 * @return (const char*) texture fle path
 * 
 */
const char* texture_path(Texture texture)
{
    SDL_assert(is_valid(texture));
    const int index = static_cast<int>(texture);
    SDL_assert(fs::exists(fs::path(TEXTURE_FILES[index])));
    return TEXTURE_FILES[index].c_str();
}

// find the texture folder path
static const fs::path find_textures_path()
{
    const std::array<fs::path, 3> candidate_paths = {fs::path("data/textures/"), fs::path("../data/textures/"),
                                                     fs::path("../../data/textures/")};

    for (const auto& path : candidate_paths)
    {
        if (fs::exists(path) && fs::is_directory(path))
        {
            return path;
        }
    }

    throw std::runtime_error("Could not find 'data/textures/' directory");
}