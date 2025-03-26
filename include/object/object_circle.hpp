#pragma once

/**
 * @file object_circle.hpp
 *
 * @brief Declaration of the ObjectCircle class for circular game objects
 *
 */
#include "object.hpp"
#include "static_list.hpp"
#include <SDL2/SDL.h>

/**
 * @class ObjectCircle
 * @brief Represents a circular game object with position, radius, and color properties
 *
 */
class ObjectCircle : public Object
{
public:
    float center_x;  ///< X-coordinate of the circle's center
    float center_y;  ///< Y-coordinate of the circle's center
    float radius;    ///< Radius of the circle
    SDL_Color color; ///< Fill color (RGBA format)

    /**
     * @brief Construct a new circle object
     *
     * @param center_x  Initial X-position in screen coordinates
     * @param center_y  Initial Y-position in screen coordinates
     * @param radius    Circle radius (must be > 0)
     * @param color     Fill color for the circle
     */
    ObjectCircle(float center_x, float center_y, float radius, SDL_Color color)
        : center_x(center_x), center_y(center_y), radius(radius), color(color)
    {
        SDL_assert(radius > 0.f);
    }

    ~ObjectCircle() {}
};

typedef StaticList<ObjectCircle, 1024U> ObjectCircleList;
