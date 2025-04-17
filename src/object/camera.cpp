/**
 * @file camera.cpp
 * @brief camera class
 */
#include "camera.hpp"

void Camera::on_key_press(SDL_Keycode key)
{
    float move_speed = 10.0f;

    switch (key)
    {
        case SDLK_w:
            position_.y -= move_speed;
            break;
        case SDLK_s:
            position_.y += move_speed;
            break;
        case SDLK_a:
            position_.x -= move_speed;
            break;
        case SDLK_d:
            position_.x += move_speed;
            break;
        case SDLK_q:
            angle_ -= 5.0f;
            break;
        case SDLK_e:
            angle_ += 5.0f;
            break;
        default:
            break;
    }
}

void Camera::on_mouse_wheel(const int wheel_y)
{
    float zoom_step = 0.1f;

    if (wheel_y > 0)
        zoom_ *= (1.0f + zoom_step);
    else if (wheel_y < 0)
        zoom_ /= (1.0f + zoom_step);
}

void Camera::on_mouse_move(const Vector2I mouse_delta, const Vector2I screen_size)
{
    position_ = {position_.x - mouse_delta.x, position_.y - mouse_delta.y};
}