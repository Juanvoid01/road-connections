#pragma once
/**
 * @file object_list.hpp
 * @brief Static list implementation with template-defined capacity
 */

#include <SDL2/SDL.h>

/**
 * @brief StaticList
 *
 * Represents a statically allocated list with fixed maximum capacity.
 *
 * @tparam T Type of elements stored in the list
 * @tparam SIZE Maximum capacity of the list (default = 1024)
 */
template <typename T, unsigned int SIZE = 1024U>
class StaticList
{
public:
    /**
     * @brief Construct a new StaticList object
     */
    StaticList() : num_objects(0) {}

    /**
     * @brief Add an element to the list
     *
     * @param object Element to add
     * @return true if element was added successfully
     * @return false if list is at full capacity
     */
    inline bool add(T object)
    {
        if (num_objects >= SIZE)
            return false;
        objects[num_objects++] = object;
        return true;
    }

    /**
     * @brief Clear the list contents
     */
    inline void clear() { num_objects = 0; }

    /**
     * @brief Get current number of elements
     *
     * @return int Number of stored elements
     */
    inline int size() const { return num_objects; }

    /**
     * @brief Get element by index
     *
     * @param index Valid index (0 <= index < size())
     * @return T Reference of requested element
     */
    inline T &get(int index)
    {
        SDL_assert(0 <= index && index < num_objects);
        return objects[index];
    }

    /**
     * @brief Get element by index
     *
     * @param index Valid index (0 <= index < size())
     * @return T Reference of requested element
     */
    inline const T &get(int index) const
    {
        SDL_assert(0 <= index && index < num_objects);
        return objects[index];
    }

    /**
     * @brief Subscript operator (non-const)
     *
     * @param index Valid index (0 <= index < size())
     * @return T& Reference to requested element
     */
    inline T &operator[](int index)
    {
        SDL_assert(0 <= index && index < num_objects);
        return objects[index];
    }

    /**
     * @brief Subscript operator (const)
     *
     * @param index Valid index (0 <= index < size())
     * @return const T& Const reference to requested element
     */
    inline const T &operator[](int index) const
    {
        SDL_assert(0 <= index && index < num_objects);
        return objects[index];
    }

    /**
     * @brief Iterator to beginning of list
     *
     * @return T* Pointer to first element
     */
    inline T *begin() { return objects; }

    /**
     * @brief Iterator to end of list
     *
     * @return T* Pointer to one past last element
     */
    inline T *end() { return objects + num_objects; }

private:
    T objects[SIZE]; ///< Internal storage array
    int num_objects; ///< Current number of stored elements
};