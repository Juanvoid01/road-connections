/**
 * @file road.cpp
 * @brief road object class
 */

#include "road.hpp"

/**
 * @brief update game logic
 * @param[in] delta_time Time elapsed since last update (seconds)
 */
void Road::update(const float delta_time) {}

/**
 * @brief Handle mouse click events
 * @param[in] mouse_pos coordinates of mouse click in screen space
 *
 */
void Road::on_click(const Vector2I mouse_pos) {}

/**
 * @brief Road Assignment operator overload.
 *      
 * @param[in] other road where to copy the data.
 * 
 * @return *this
 */
Road& Road::operator=(const Road& other)
{
    if (this != &other)  // not a self-assignment
    {
        this->start_pos_ = other.start_pos_;
        this->end_pos_ = other.end_pos_;
        this->state_ = other.state_;
    }
    return *this;
}