#ifndef RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
#define RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Input-related functions: gamepads
 */
class Gamepad {
 public:
    Gamepad(int gamepadNumber = 0) {
        set(gamepadNumber);
    }
    int number;

    GETTERSETTER(int, Number, number)

    auto operator=(const Gamepad& gamepad) -> Gamepad&
    {
        set(gamepad);
        return *this;
    }

    auto operator=(int gamepadNumber) -> Gamepad&
    {
        set(gamepadNumber);
        return *this;
    }

    operator int() const { return number; }

    /**
     * Detect if a gamepad is available
     */
    inline auto IsAvailable() const -> bool
    {
        return ::IsGamepadAvailable(number);
    }

    /**
     * Detect if a gamepad is available
     */
    static inline auto IsAvailable(int number) -> bool
    {
        return ::IsGamepadAvailable(number);
    }

    /**
     * Return gamepad internal name id
     */
    auto GetName() const -> std::string
    {
        return ::GetGamepadName(number);
    }

    /**
     * Return gamepad internal name id
     */
    operator std::string() const {
        return GetName();
    }

    /**
     * Detect if a gamepad button has been pressed once
     */
    inline auto IsButtonPressed(int button) const -> bool
    {
        return ::IsGamepadButtonPressed(number, button);
    }

    /**
     * Detect if a gamepad button is being pressed
     */
    inline auto IsButtonDown(int button) const -> bool
    {
        return ::IsGamepadButtonDown(number, button);
    }

    /**
     * Detect if a gamepad button has been released once
     */
    inline auto IsButtonReleased(int button) const -> bool
    {
        return ::IsGamepadButtonReleased(number, button);
    }

    /**
     * Detect if a gamepad button is NOT being pressed
     */
    inline auto IsButtonUp(int button) const -> bool
    {
        return ::IsGamepadButtonUp(number, button);
    }

    /**
     * Get the last gamepad button pressed
     */
    inline auto GetButtonPressed() const -> int
    {
        return ::GetGamepadButtonPressed();
    }

    /**
     * Return gamepad axis count for a gamepad
     */
    inline auto GetAxisCount() const -> int
    {
        return ::GetGamepadAxisCount(number);
    }

    /**
     * Return axis movement value for a gamepad axis
     */
    inline auto GetAxisMovement(int axis) const -> float
    {
        return ::GetGamepadAxisMovement(number, axis);
    }

    inline auto SetMappings(const std::string& mappings) -> int
    {
        return SetGamepadMappings(mappings.c_str());
    }

 private:
    inline void set(int gamepadNumber) {
        number = gamepadNumber;
    }
};
}  // namespace raylib

using RGamepad = raylib::Gamepad;

#endif  // RAYLIB_CPP_INCLUDE_GAMEPAD_HPP_
