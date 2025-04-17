#pragma once

/**
 * @file city.hpp
 * @brief city object class
 */

#include "mathematics.hpp"
#include "texture_manager.hpp"
#include <SDL2/SDL.h>

/**
 * @class City class
 */
class City
{
   public:

    /**
     * @enum City::State enum
     */
    enum class State
    {
        IDLE,
        SELECTED,
        UNBOUGHT,
        COUNT
    };

    City() : hitbox_(), generated_money_(0.f), state_(State::IDLE) {}

    City(Vector2F pos, float generated_money, State state)
        : hitbox_({pos.x, pos.y, WIDTH, WIDTH}), generated_money_(generated_money), state_(state)

    {}

    /**
     * @brief City copy constructor
     *     
     * @param[in] city other city 
     */
    City(const City& city) : hitbox_(city.hitbox_), generated_money_(city.generated_money_), state_(city.state_) {}

    ~City() {}

    /**
     * @brief update game logic
     * @param[in] delta_time Time elapsed since last update (seconds)
     */
    void update(const float delta_time);

    /**
     * @brief Handle mouse click events
     * @param[in] mouse_pos coordinates of mouse click in screen space
     *
     */
    void on_click(const Vector2I mouse_pos);

    /**
     * @brief get generated money
     * @return float generated_money_
     */
    inline float money() const { return generated_money_; }

    /**
     * @brief get texture id
     * @return Texture
     */
    inline Texture texture() const { return state_texture(state_); }

    /**
     * @brief get hitbox
     * @return HitboxRect hitbox_
     */
    inline HitboxRect hitbox() const { return hitbox_; }

    /**
     * @brief get state
     * @return City::State state_
     */
    inline State state() const { return state_; }

    /**
     * @brief City Assignment operator overload.
     *      
     * @param[in] other city where to copy the data.
     * 
     * @return *this
     */
    City& operator=(const City& other);

   private:

    static constexpr float WIDTH = 100.f;
    static constexpr float MONEY_PER_SECOND = 10.f;

    HitboxRect hitbox_;
    float generated_money_;
    State state_;

    // check if state is valid. True if (state >= 0 && state <= State::COUNT)
    static inline bool is_valid(State state) { return int(state) >= 0 && int(state) <= int(State::COUNT); }

    // return texture of the given state
    inline Texture state_texture(State state) const
    {
        SDL_assert(is_valid(state));

        static const Texture state_textures[3] = {Texture::CITY_IDLE, Texture::CITY_SELECTED, Texture::CITY_UNBOUGHT};

        return state_textures[static_cast<int>(state)];
    }
};