#pragma once

/**
 * @file game_info.hpp
 * @brief Game info definition
 */

#include "city.hpp"
#include "mathematics.hpp"
#include "road.hpp"
#include <vector>

// maximum number of cities
constexpr int MAX_CITIES = 1024;

// vector of cities type
typedef std::vector<City> CitiesList;

// vector of roads type
typedef std::vector<Road> RoadList;

/**
 * @brief game information
 * 
 * - cities array
 * - number of cities
 * - spawn camera position
 * - money
 */
struct GameInfo
{
    CitiesList cities;        // city list
    RoadList roads;           // road list
    Vector2F spawn_position;  // spawn camera position
    float money;              // total generated money
};