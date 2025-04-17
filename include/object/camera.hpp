#pragma once

/**
 * @file camera.hpp
 * @brief camera class
 */

#include "mathematics.hpp"

/**
 * @class Camera
 * @brief Camera class
 */
class Camera
{
   public:
    /**
     * @brief Camera coordinates position.
     */
    inline Vector2F position() const { return position_; }

    /**
     * @brief Zoom factor (1.0 = normal size).
     */
    inline float zoom() const { return zoom_; }

    /**
     * @brief Rotation angle in degrees.
     */
    inline float angle() const { return angle_; }

    void on_mouse_wheel(int wheel_y);
    void on_key_press(const SDL_Keycode key);
    void on_mouse_move(const Vector2I mouse_pos, const Vector2I screen_size);

    Camera() : position_({0.f, 0.f}), zoom_(1.f), angle_(0.f) {}

    Camera(Vector2F pos, float zoom = 1.f, float angle = 0.f) : position_(pos), zoom_(zoom), angle_(angle) {}

   private:
    Vector2F position_;  // coordinates position
    float zoom_;         // Zoom factor (1.0 = normal size).
    float angle_;        // Rotation angle in degrees.
};
