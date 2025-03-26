#pragma once

#include "object_circle.hpp"

class City : public ObjectCircle
{
public:
    enum class State : int
    {
        IDLE = 0,
        UNSELECTED = 1,
        SELECTED = 2
    };
    const SDL_Color IDLE_COLOR = {200, 200, 200, 255};
    const SDL_Color UNSELECTED_COLOR = {0, 0, 120, 255};
    const SDL_Color SELECTED_COLOR = {0, 200, 0, 255};
    City(float x, float y, int radius)
        : ObjectCircle(x, y, radius, IDLE_COLOR), state(State::IDLE), generated_money(0.f) {}

    void update(float delta_time);
    void on_click(float mouse_x, float mouse_y);

    inline float get_generated_money() const { return generated_money; }
    inline void clear_generated_money() { generated_money = 0; }

private:
    State state;
    float generated_money;

    const float MONEY_PER_SEC = 10.f;



    inline SDL_Color state_color(State state) const
    {
        static const SDL_Color state_colors[3] = {IDLE_COLOR, UNSELECTED_COLOR, SELECTED_COLOR};
        return state_colors[static_cast<int>(state)];
    }
};