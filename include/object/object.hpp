#pragma once

/**
 * @file object.hpp
 * @brief Abstract base class interface for game objects
 */

/**
 * @class Object
 * @brief Abstract base class defining core object behavior
 *
 */
class Object
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Object() = default;

    /**
     * @brief Update object state
     * @param[in] delta_time Time elapsed since last update (seconds)
     * @note This method should contain all game logic and state updates
     */
    virtual void update(float delta_time) = 0;

    /**
     * @brief Handle mouse click events on this object
     * @param[in] mouse_x X-coordinate of mouse click in screen space
     * @param[in] mouse_y Y-coordinate of mouse click in screen space
     *
     */
    virtual void on_click(float mouse_x, float mouse_y) = 0;

protected:
    /**
     * @brief Protected constructor to enforce abstract base class usage
     * @note Prevents direct instantiation while allowing inheritance
     */
    Object() = default;
};
