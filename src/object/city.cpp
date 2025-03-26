#include "city.hpp"

static inline bool is_point_in_circle(float px, float py, float cx, float cy, float radius);

void City::update(float delta_time)
{
    if (state != State::IDLE)
    {
        generated_money += MONEY_PER_SEC * delta_time;
    }
}

void City::on_click(float mouse_x, float mouse_y)
{
    if (is_point_in_circle(mouse_x, mouse_y, center_x, center_y, radius))
    {
        switch (state)
        {
        case State::UNSELECTED:
            state = State::SELECTED;
            break;
        case State::SELECTED:
            break;
        default: // no action
            break;
        }
        color = state_color(state);
    }
    else
    {
        if (state == State::SELECTED)
        {
            state = State::UNSELECTED;
            color = state_color(state);
        }
    }
}

inline bool is_point_in_circle(float px, float py, float cx, float cy, float radius)
{
    float dx = px - cx;
    float dy = py - cy;
    return (dx * dx + dy * dy) < (radius * radius);
}