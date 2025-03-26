/**
 * @file event_handler.hpp
 * @brief SDL Event handling subsystem for processing input events
 */

#include "event_handler.hpp"
#include "game_controller.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Internal helper to process keyboard events
 * @param keysym SDL_Keysym containing key information
 */
static void handle_keydown(const SDL_Keysym &keysym);

/**
 * @brief Process all pending SDL events
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
bool EventHandler::update()
{
    SDL_Event event;

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
            handle_keydown(event.key.keysym);
            break;

        case SDL_KEYUP:
            printf("Key released: %s\n", SDL_GetKeyName(event.key.keysym.sym));
            break;

        // Mouse motion
        case SDL_MOUSEMOTION:
            printf("Mouse moved to (%d, %d)\n",
                   event.motion.x, event.motion.y);
            break;

        // Mouse clicked events
        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse button %d pressed at (%d, %d)\n",
                   event.button.button, event.button.x, event.button.y);

            // Check specific mouse buttons
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                printf("Left mouse button pressed\n");
            }
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                printf("Right mouse button pressed\n");
            }
            break;

        case SDL_MOUSEBUTTONUP:
            printf("Mouse button %d released at (%d, %d)\n",
                   event.button.button, event.button.x, event.button.y);
            break;

        // Mouse wheel event
        case SDL_MOUSEWHEEL:
            printf("Mouse wheel scrolled %s by %d units\n",
                   event.wheel.y > 0 ? "up" : "down", abs(event.wheel.y));
            break;
        }
    }
    return true;
}

/**
 * @brief Internal helper to process keyboard events
 * @param keysym SDL_Keysym containing key information
 */
static void handle_keydown(const SDL_Keysym &keysym)
{
    switch (keysym.sym)
    {
    case SDLK_ESCAPE:
        printf("Escape key pressed (NOTE: Not closing application)\n");
        break;
    case SDLK_w:
        printf("W key pressed\n");
        break;
    case SDLK_a:
        printf("A key pressed\n");
        break;
    case SDLK_s:
        printf("S key pressed\n");
        break;
    case SDLK_d:
        printf("D key pressed\n");
        break;
    default:
        printf("Key pressed: %s\n", SDL_GetKeyName(keysym.sym));
        break;
    }
}