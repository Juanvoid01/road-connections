#pragma once

/**
 * @file event_handler.hpp
 * @brief SDL Event handling subsystem for processing input events
 */

/**
 * @namespace EventHandler
 * @brief Handles SDL event processing including keyboard, mouse, and window events
 *
 * Provides a centralized interface for polling and processing SDL events.
 * Manages application closure events and user input handling.
 */
namespace EventHandler
{

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
    bool update();
}; // namespace EventHandler