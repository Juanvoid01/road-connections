/**
 * @file event_handler.cpp
 * @brief SDL Event handling subsystem for processing input events
 */

#include "event_handler.hpp"
#include "game_controller.hpp"
#include "renderer.hpp"
#include <SDL2/SDL.h>

static bool dragging = false;
static float last_drag_x = 0.0f;
static float last_drag_y = 0.0f;

/**
 * @brief Process all pending SDL events
 * 
 * @param[in] renderer
 * 
 * @return bool - Application continuation status
 * @retval true  - Continue running
 * @retval false - Exit requested
 *
 * @details Checks all event types:
 * - Window closure (SDL_QUIT)
 * - Keyboard input (key press/release)
 * - Mouse motion/buttons/wheel
 *
 */
bool EventHandler::update(const Renderer& renderer)
{
    SDL_Event event;

    int window_width, window_height;
    renderer.get_window_size(window_width, window_height);
    const Vector2I window_size = {window_width, window_height};

    int mouse_dx, mouse_dy;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            // Window close event
            case SDL_QUIT:
                return false;
                break;

            // Keyboard events
            case SDL_KEYDOWN:
                GameController::on_key_press(event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                printf("Key released: %s\n", SDL_GetKeyName(event.key.keysym.sym));
                break;

            // Mouse motion
            case SDL_MOUSEMOTION:

                if (dragging)
                {
                    mouse_dx = event.motion.x - last_drag_x;
                    mouse_dy = event.motion.y - last_drag_y;
                } else
                {
                    mouse_dx = 0;
                    mouse_dy = 0;
                }
                //printf("Mouse moved to (%d, %d)\n", event.motion.x, event.motion.y);
                GameController::on_mouse_move({event.motion.x, event.motion.y}, {mouse_dx, mouse_dy}, window_size);

                last_drag_x = event.motion.x;
                last_drag_y = event.motion.y;
                break;

            // Mouse clicked events
            case SDL_MOUSEBUTTONDOWN:

                printf("Mouse button %d pressed at (%d, %d)\n", event.button.button, event.button.x, event.button.y);

                // Check specific mouse buttons
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    printf("Left mouse button pressed\n");
                } else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    printf("Right mouse button pressed\n");
                    dragging = true;
                    last_drag_x = static_cast<float>(event.button.x);
                    last_drag_y = static_cast<float>(event.button.y);
                }

                GameController::on_click({event.button.x, event.button.y});

                break;

            case SDL_MOUSEBUTTONUP:
                printf("Mouse button %d released at (%d, %d)\n", event.button.button, event.button.x, event.button.y);

                if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    printf("Right mouse button pressed\n");
                    dragging = false;
                }
                break;

            // Mouse wheel event
            case SDL_MOUSEWHEEL:
                GameController::on_mouse_wheel(event.wheel.y);

                //printf("Mouse wheel scrolled %s by %d units\n", event.wheel.y > 0 ? "up" : "down", abs(event.wheel.y));
                break;

            /*case SDL_FINGERDOWN: {
                // event.tfinger.x and .y are in [0,1] as a fraction of the window
                float px = event.tfinger.x * window_width;
                float py = event.tfinger.y * window_height;
                printf("Touch down at (%f, %f), finger %llu\n", px, py, (unsigned long long)event.tfinger.fingerId);

                // if you already have on_click taking pixel coords, reuse it:
                GameController::on_click({(int)px, (int)py});
                break;
            }

            case SDL_FINGERUP: {
                float px = event.tfinger.x * window_width;
                float py = event.tfinger.y * window_height;
                printf("Touch up at (%f, %f), finger %llu\n", px, py, (unsigned long long)event.tfinger.fingerId);

                // if you want a dedicated touch-end callback:
                GameController::on_touch_end({(int)px, (int)py}, event.tfinger.fingerId);
                break;
            }

            case SDL_FINGERMOTION: {
                // compute delta in normalized space, then scale
                float dx = event.tfinger.dx * window_width;
                float dy = event.tfinger.dy * window_height;
                float px = event.tfinger.x * window_width;
                float py = event.tfinger.y * window_height;
                //printf("Touch motion at (%f, %f) Δ(%f, %f), finger %llu\n", px, py, dx, dy, (unsigned long long)event.tfinger.fingerId);

                // optionally treat as mouse move:
                GameController::on_mouse_move({(int)px, (int)py}, {(int)dx, (int)dy}, window_size);
                break;
            }*/
            default:  // nothing
                break;
        }
    }
    return true;
}