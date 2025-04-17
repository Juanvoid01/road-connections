#pragma once

/**
 * @file game_controller.hpp
 * @brief Game controller logic subsystem
 */

#include "camera.hpp"
#include "game_info.hpp"
#include "mathematics.hpp"

/**
 * @namespace GameController
 * @brief Handles game logic
 */
namespace GameController
{
    /**
     * @brief initialize the game
     */
    void init();

    /**
     * @brief update game logic
     * @param[in] delta_time Time elapsed since last update (seconds)
     */
    void update(const float delta_time);

    /**
     * @brief Handle mouse click events
     * @param[in] mouse_pos coordinates of mouse click in screen space
     *
     */
    void on_click(const Vector2I mouse_pos);

    void on_mouse_wheel(const int wheel_y);
    void on_key_press(const SDL_Keycode key);
    void on_mouse_move(const Vector2I mouse_pos, const Vector2I mouse_delta, const Vector2I screen_size);

    /**
     * @brief get cities list
     *
     * @return (const CitiesList&) cities
     */
    const CitiesList& get_cities();

    /**
     * @brief get roads list
     *
     * @return (const RoadList&) cities
     */
    const RoadList& get_roads();

    /**
     * @brief get camera
     *
     * @return (const Camera&) camera
     */
    const Camera& get_camera();

};  // namespace GameController