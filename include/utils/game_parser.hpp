#pragma once
/**
 * @file game_parser.hpp
 * @brief Game parser subsystem
 */

#include "game_info.hpp"
#include <cstdint>

/**
  * @namespace GameParser
  * @brief Handles game save and load parsing file logic
  */
namespace GameParser
{
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
    bool load(GameInfo& game_info, uint32_t game_id);

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
    bool save(const GameInfo& game_info, uint32_t game_id);

};  // namespace GameParser