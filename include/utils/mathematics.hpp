#pragma once

/**
 * @file mathematics.hpp
 * @brief Mathematics subsystem
 */

#include <SDL2/SDL.h>

// two dimensional float position vector (x,y)
typedef SDL_Point Vector2I;

// two dimensional float size vector (x,y)
typedef SDL_FPoint Vector2F;

// two dimensional float rectangle hitbox (x,y,w,h). (x,y) is the top left corner.
typedef SDL_FRect HitboxRect;

// two dimensional float circle hitbox (x,y,center)
struct HitboxCircle
{
    Vector2F center;
    float radius;
};

inline Vector2F to_vector2F(const Vector2I vector)
{
    return {static_cast<float>(vector.x), static_cast<float>(vector.y)};
}

inline Vector2I to_vector2I(const Vector2F vector)
{
    return {static_cast<int>(vector.x), static_cast<int>(vector.y)};
}

/**
 * @brief Checks if a point is inside a the rectangle hitbox
 *
 * @param[in] position - position to check
 * @param[in] rect - rectangle hitbox to check against
 *
 * @return bool - True if the point is inside the rectangle, false otherwise
 */
inline bool is_inside(const Vector2F position, const HitboxRect& rect)
{
    return SDL_PointInFRect(&position, &rect);
}

/**
 * @brief Checks if a point is inside a the circle hitbox
 *
 * @param[in] position - position to check
 * @param[in] circle - circle hitbox to check against
 *
 * @return bool - True if the point is inside the circle, false otherwise
 */
inline bool is_inside(const Vector2F position, const HitboxCircle& circle)
{
    const float dx = position.x - circle.center.x;
    const float dy = position.y - circle.center.y;
    const float distance_squared = dx * dx + dy * dy;
    return distance_squared <= (circle.radius * circle.radius);
}

inline SDL_Rect hitboxRect_to_SDL_Rect(const HitboxRect& hitbox)
{
    return {static_cast<int>(hitbox.x), static_cast<int>(hitbox.y), static_cast<int>(hitbox.w),
            static_cast<int>(hitbox.h)};
}

inline Vector2F window_pos_to_world_pos(Vector2F window_pos, Vector2F camera_pos, float zoom)
{
    return {(window_pos.x / zoom) + camera_pos.x, (window_pos.y / zoom) + camera_pos.y};
}