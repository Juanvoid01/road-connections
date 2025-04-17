/**
 * @file game_parser.cpp
 * @brief Game parser subsystem
 */

#include "game_parser.hpp"
#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

// find saves folder path
static const fs::path find_saves_path();

// saves folder path
static const fs::path SAVES_PATH = find_saves_path();

/**
 * @brief read and load the game information from file
 *
 * Read game info from SVES_PATH/game_id file. 
 * Game info must have the following pattern:
 *  
 *  num_cities (0 to 1024)
 *  city_pos_x city_pos_y city_generated_money
 *  city_pos_x city_pos_y city_generated_money
 *  city_pos_x city_pos_y city_generated_money
 *  ... (repeats num_cities_times)
 *  + money spawn_pos_x spawn_pos_y 
 * 
 * @param[in] game_id game identifier
 *
 * @return (bool) success
 * @retval true  - Correct game info parsing
 * @retval false - Incorrect game info
 * 
 */
bool GameParser::load(GameInfo& game_info, uint32_t game_id)
{
    const std::string file_path = std::string(SAVES_PATH) + std::to_string(game_id) + ".txt";
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + std::string(file_path));
        return false;
    }
    std::string line;

    if (!std::getline(file, line))
    {
        file.close();
        throw std::runtime_error("Missing game information");
        return false;
    }
    int num_cities = std::stoi(line);

    if (num_cities <= 0 || num_cities >= MAX_CITIES)
    {
        file.close();
        throw std::runtime_error("Incorrect number of cities");
        return false;
    }
    game_info.cities.resize(num_cities);

    // Read city data
    for (int i = 0; i < num_cities; ++i)
    {
        if (!std::getline(file, line))
        {
            file.close();
            throw std::runtime_error("Missing game information");
            return false;
        }

        std::istringstream iss(line);
        float pos_x, pos_y, generated_money;
        int bought;

        if (!(iss >> pos_x >> pos_y >> bought >> generated_money))
        {
            file.close();
            throw std::runtime_error("Invalid city data at line " + std::to_string(i + 1));
            return false;
        }

        // Security: Validate input
        if (generated_money < 0.f)
        {
            file.close();
            throw std::runtime_error("Negative generated money at line " + std::to_string(i + 1));
            return false;
        }

        // Create city
        const City::State state = bought ? City::State::IDLE : City::State::UNBOUGHT;
        game_info.cities[i] = City({pos_x, pos_y}, generated_money, state);
    }

    // final game information

    if (!std::getline(file, line))
    {
        file.close();
        throw std::runtime_error("Missing game information");
        return false;
    }

    std::istringstream iss(line);

    char end_information_char;
    if (!(iss >> end_information_char))
    {
        file.close();
        throw std::runtime_error("Invalid ending game info data");
        return false;
    }

    if (end_information_char != '+')
    {
        file.close();
        throw std::runtime_error("Invalid end information char");
        return false;
    }

    if (!(iss >> game_info.money >> game_info.spawn_position.x >> game_info.spawn_position.y))
    {
        file.close();
        throw std::runtime_error("Invalid ending game info data");
        return false;
    }

    file.close();
    return true;
}

/**
 * @brief save the game information into a file
 *
 * Game info must have the following pattern:
 *  
 *  num_cities (0 to 1024)
 *  city_pos_x city_pos_y city_generated_money
 *  city_pos_x city_pos_y city_generated_money
 *  city_pos_x city_pos_y city_generated_money
 *  ... (repeats num_cities_times)
 *  + money spawn_pos_x spawn_pos_y 
 * 
 * @param[in] game_info game information
 * @param[in] game_id game identifier
 *
 * @return (bool) success
 * @retval true  - saved
 * @retval false - error
 * 
 */
bool GameParser::save(const GameInfo& game_info, uint32_t game_id)
{
    std::string file_path = std::string(SAVES_PATH) + std::to_string(game_id) + ".txt";
    std::ofstream file(file_path);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file for writing: " + file_path);
        return false;
    }

    int num_cities = game_info.cities.size();
    file << num_cities << '\n';

    for (int i = 0; i < num_cities; ++i)
    {
        const auto& city = game_info.cities[i];
        int bought = (city.state() == City::State::IDLE) ? 1 : 0;
        file << city.hitbox().x << ' ' << city.hitbox().y << ' ' << bought << ' ' << city.money() << '\n';
    }

    file << "+ " << game_info.money << ' ' << game_info.spawn_position.x << ' ' << game_info.spawn_position.y << '\n';

    return true;
}

// find saves folder path
static const fs::path find_saves_path()
{
    std::array<fs::path, 3> candidate_paths = {fs::path("data/saves/"), fs::path("../data/saves/"),
                                               fs::path("../../data/saves/")};

    for (const auto& path : candidate_paths)
    {
        if (fs::exists(path) && fs::is_directory(path))
        {
            return path;
        }
    }

    throw std::runtime_error("Could not find 'data/saves/' directory");
}