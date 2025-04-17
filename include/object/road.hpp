#pragma once

/**
 * @file road.hpp
 * @brief road object class
 */

#include "mathematics.hpp"
#include "texture.hpp"

/**
 * @class Road class
 */
class Road
{
   public:
    /**
     * @enum Road::State enum
     */
    enum class State
    {
        NOT_BUILT,
        BUILT,
        COUNT
    };

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
     * @brief get texture id
     * @return Texture Road
     */
    static inline Texture texture() { return Texture::ROAD; }

    /**
     * @brief get start position of the road (bottom left corner)
     * @return Vector2F start_pos_
     */
    inline Vector2F start_pos() { return start_pos_; }

    /**
     * @brief get end position of the road (top right corner)
     * @return Vector2F end_pos_
     */
    inline Vector2F end_pos() { return end_pos_; }

    /**
     * @brief get road state
     * @return Road::State Road
     */
    inline State state() { return state_; }

    Road() : start_pos_(), end_pos_(), state_(State::NOT_BUILT) {}

    Road(Vector2F start_pos, Vector2F end_pos, State state) : start_pos_(start_pos), end_pos_(end_pos), state_(state) {}

    /**
     * @brief Road copy constructor
     *     
     * @param[in] road other road 
     */
    Road(const Road& road) : start_pos_(road.start_pos_), end_pos_(road.end_pos_), state_(road.state_) {}

    ~Road() {}

    /**
     * @brief Road Assignment operator overload.
     *      
     * @param[in] other road where to copy the data.
     * 
     * @return *this
     */
    Road& operator=(const Road& other);

   private:
    Vector2F start_pos_;  // bottom left corner
    Vector2F end_pos_;    // top right corner
    State state_;         // road state
};