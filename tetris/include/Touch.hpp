#ifndef RAYLIB_CPP_INCLUDE_TOUCH_HPP_
#define RAYLIB_CPP_INCLUDE_TOUCH_HPP_

#include "./raylib.hpp"

namespace raylib {
/**
 * Input-related functions: touch
 */
class Touch {
 public:
    /**
     * Get touch position X for touch point 0 (relative to screen size)
     */
     inline static auto GetX() -> int
     {
         return ::GetTouchX();
     }

    /**
     * Get touch position Y for touch point 0 (relative to screen size)
     */
     inline static auto GetY() -> int
     {
         return ::GetTouchY();
     }

    /**
     * Get touch position XY for a touch point index (relative to screen size)
     */
     inline static auto GetPosition(int index) -> Vector2
     {
         return ::GetTouchPosition(index);
     }

    /**
     * Get touch point identifier for given index
     */
     inline static auto GetPointId(int index) -> int
     {
         return ::GetTouchPointId(index);
     }

    /**
     * Get number of touch points
     */
     inline static auto GetPointCount() -> int
     {
         return ::GetTouchPointCount();
     }
};
}  // namespace raylib

using RTouch = raylib::Touch;

#endif  // RAYLIB_CPP_INCLUDE_TOUCH_HPP_
