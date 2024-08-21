#ifndef RAYLIB_CPP_INCLUDE_MOUSE_HPP_
#define RAYLIB_CPP_INCLUDE_MOUSE_HPP_

#include "./raylib.hpp"
#include "./Vector2.hpp"

namespace raylib {
/**
 * Input-related functions: mouse
 */
class Mouse {
 public:
    /**
     * Detect if a mouse button has been pressed once
     */
     static inline auto IsButtonPressed(int button) -> bool
     {
         return ::IsMouseButtonPressed(button);
     }

    /**
     * Detect if a mouse button is being pressed
     */
     static inline auto IsButtonDown(int button) -> bool
     {
         return ::IsMouseButtonDown(button);
     }

    /**
     * Detect if a mouse button has been released once
     */
     static inline auto IsButtonReleased(int button) -> bool
     {
         return ::IsMouseButtonReleased(button);
     }

     static inline auto IsButtonUp(int button) -> bool
     {
         return ::IsMouseButtonUp(button);
     }

     static inline auto GetX() -> int
     {
         return ::GetMouseX();
     }

     static inline auto GetY() -> int
     {
         return ::GetMouseY();
     }

    static inline void SetX(int x) {
        ::SetMousePosition(x, GetY());
    }

    static inline void SetY(int y) {
        ::SetMousePosition(GetX(), y);
    }

    static inline auto GetPosition() -> Vector2
    {
        return ::GetMousePosition();
    }

    static inline void SetPosition(int x, int y) {
        ::SetMousePosition(x, y);
    }

    static inline void SetPosition(::Vector2 position) {
        ::SetMousePosition(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * Get mouse delta between frames
     */
    static inline auto GetDelta() -> Vector2
    {
        return ::GetMouseDelta();
    }

    static inline void SetOffset(int offsetX = 0, int offsetY = 0) {
        ::SetMouseOffset(offsetX, offsetY);
    }

    static inline void SetOffset(::Vector2 offset) {
        ::SetMouseOffset(static_cast<int>(offset.x), static_cast<int>(offset.y));
    }

    static inline void SetScale(float scaleX = 1.0f, float scaleY = 1.0f) {
        ::SetMouseScale(scaleX, scaleY);
    }

    static inline void SetScale(::Vector2 scale) {
        ::SetMouseScale(scale.x, scale.y);
    }

    /**
     * Get mouse wheel movement for X or Y, whichever is larger
     */
    static inline auto GetWheelMove() -> float
    {
        return ::GetMouseWheelMove();
    }

    /**
     * Get mouse wheel movement for both X and Y
     *
     * @see ::GetMouseWheelMoveV()
     */
    static inline auto GetWheelMoveV() -> Vector2
    {
        return GetMouseWheelMoveV();
    }

    /**
     * Sets the current mouse cursor icon.
     *
     * @see ::MouseCursor
     */
    static inline void SetCursor(int cursor = MOUSE_CURSOR_DEFAULT) {
        ::SetMouseCursor(cursor);
    }

    /**
     * Get touch position X for touch point 0 (relative to screen size)
     */
    static inline auto GetTouchX() -> int
    {
        return ::GetTouchX();
    }

    /**
     * Get touch position Y for touch point 0 (relative to screen size)
     */
    static inline auto GetTouchY() -> int
    {
        return ::GetTouchY();
    }

    /**
     * Get touch position XY for a touch point index (relative to screen size)
     */
    static inline auto GetTouchPosition(int index) -> Vector2
    {
        return ::GetTouchPosition(index);
    }

    /**
     * Get a ray trace from mouse position
     */
    static inline auto GetRay(::Vector2 mousePosition, const ::Camera& camera) -> Ray
    {
        return ::GetMouseRay(mousePosition, camera);
    }

    /**
     * Get a ray trace from mouse position
     */
    static inline auto GetRay(const ::Camera& camera) -> Ray
    {
        return ::GetMouseRay(::GetMousePosition(), camera);
    }
};
}  // namespace raylib

using RMouse = raylib::Mouse;

#endif  // RAYLIB_CPP_INCLUDE_MOUSE_HPP_
