/**
 * @file game_controller.cpp
 * @brief Game controller logic subsystem
 */

#include "game_controller.hpp"
#include "game_parser.hpp"
#include <array>

constexpr int NUM_GAMES = 1;

static std::array<GameInfo, NUM_GAMES> games;

static Camera camera;
static uint32_t game_id = 0;

/**
 * @brief initialize the game
 */
void GameController::init()
{
    GameParser::load(games[game_id], game_id);
    camera = Camera(games[game_id].spawn_position);
}

/**
 * @brief update game logic
 * @param[in] delta_time Time elapsed since last update (seconds)
 */
void GameController::update(const float delta_time)
{
    for (City& city : games[game_id].cities)
    {
        city.update(delta_time);
    }
}

/**
 * @brief Handle mouse click events
 * @param[in] mouse_pos coordinates of mouse click in screen space
 *
 */
void GameController::on_click(const Vector2I mouse_pos)
{
    const Vector2F camera_pos = camera.position();
    const float zoom = camera.zoom();

    const Vector2I mouse_world_pos = to_vector2I(window_pos_to_world_pos(to_vector2F(mouse_pos), camera_pos, zoom));

    for (City& city : games[game_id].cities)
    {
        city.on_click(mouse_world_pos);
    }
}

void GameController::on_mouse_wheel(int wheel_y)
{
    camera.on_mouse_wheel(wheel_y);
}

void GameController::on_key_press(SDL_Keycode key)
{
    camera.on_key_press(key);
}

void GameController::on_mouse_move(const Vector2I mouse_pos, const Vector2I mouse_delta, const Vector2I screen_size)
{
    camera.on_mouse_move(mouse_delta, screen_size);
}

/**
 * @brief get cities list
 *
 * @return (const CitiesList&) cities
 */
const CitiesList& GameController::get_cities()
{
    return games[game_id].cities;
}

/**
 * @brief get roads list
 *
 * @return (const RoadList&) cities
 */
const RoadList& GameController::get_roads()
{
    return games[game_id].roads;
}

/**
 * @brief get camera
 *
 * @return (const Camera&) camera
 */
const Camera& GameController::get_camera()
{
    return camera;
}