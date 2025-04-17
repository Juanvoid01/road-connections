/**
 * @file city.cpp
 * @brief city object class
 */

#include "city.hpp"

void City::update(const float delta_time)
{
    if (state_ != State::IDLE)
    {
        generated_money_ += MONEY_PER_SECOND * delta_time;
    }
}

void City::on_click(const Vector2I mouse_pos)
{
    if (is_inside(to_vector2F(mouse_pos), hitbox_))
    {
        // Check if the city is already selected
        if (state_ == State::SELECTED)
        {
            state_ = State::IDLE;
        } else
        {
            state_ = State::SELECTED;
        }
    } else
    {
        // clicked outside hitbox
        if (state_ == State::SELECTED)
        {
            state_ = State::IDLE;
        }
    }
}

/**
 * @brief City Assignment operator overload.
 *      
 * @param[in] other city where to copy the data.
 * 
 * @return *this
 */
City& City::operator=(const City& other)
{
    if (this != &other)  // not a self-assignment
    {
        this->hitbox_ = other.hitbox_;
        this->generated_money_ = other.generated_money_;
        this->state_ = other.state_;
    }
    return *this;
}