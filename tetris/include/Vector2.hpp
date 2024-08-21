#ifndef RAYLIB_CPP_INCLUDE_VECTOR2_HPP_
#define RAYLIB_CPP_INCLUDE_VECTOR2_HPP_

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

#include "./raylib.hpp"
#include "./raymath.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Vector2 type
 */
class Vector2 : public ::Vector2 {
 public:
    Vector2(const ::Vector2& vec) : ::Vector2{vec.x, vec.y} {}

    Vector2(float x, float y) : ::Vector2{x, y} {}
    Vector2(float x) : ::Vector2{x, 0} {}
    Vector2() : ::Vector2{0, 0} {}

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)

    /**
     * Set the Vector2 to the same as the given Vector2.
     */
    auto operator=(const ::Vector2& vector2) -> Vector2&
    {
        set(vector2);
        return *this;
    }

    /**
     * Determine whether or not the vectors are equal.
     */
    auto operator==(const ::Vector2& other) -> bool
    {
        return x == other.x
            && y == other.y;
    }

    /**
     * Determines if the vectors are not equal.
     */
    auto operator!=(const ::Vector2& other) -> bool
    {
        return !(*this == other);
    }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Add two vectors (v1 + v2)
     */
    inline auto Add(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Add(*this, vector2);
    }

    /**
     * Add two vectors (v1 + v2)
     */
    inline auto operator+(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Add(*this, vector2);
    }

    /**
     * Add two vectors (v1 + v2)
     */
    auto operator+=(const ::Vector2& vector2) -> Vector2&
    {
        set(Vector2Add(*this, vector2));

        return *this;
    }

    /**
     * Subtract two vectors (v1 - v2)
     */
    inline auto Subtract(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Subtract(*this, vector2);
    }

    /**
     * Subtract two vectors (v1 - v2)
     */
    inline auto operator-(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Subtract(*this, vector2);
    }

    /**
     * Add two vectors (v1 + v2)
     */
    auto operator-=(const ::Vector2& vector2) -> Vector2&
    {
        set(Vector2Subtract(*this, vector2));

        return *this;
    }

    /**
     * Negate vector
     */
    inline auto Negate() const -> Vector2
    {
        return Vector2Negate(*this);
    }

    /**
     * Negate vector
     */
    inline auto operator-() const -> Vector2
    {
        return Vector2Negate(*this);
    }

    /**
     * Multiply vector by vector
     */
    inline auto Multiply(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Multiply(*this, vector2);
    }

    /**
     * Multiply vector by vector
     */
    inline auto operator*(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Multiply(*this, vector2);
    }

    /**
     * Multiply vector by vector
     */
    auto operator*=(const ::Vector2& vector2) -> Vector2&
    {
        set(Vector2Multiply(*this, vector2));

        return *this;
    }

    /**
     * Scale vector (multiply by value)
     */
    inline auto Scale(const float scale) const -> Vector2
    {
        return Vector2Scale(*this, scale);
    }

    /**
     * Scale vector (multiply by value)
     */
    inline auto operator*(const float scale) const -> Vector2
    {
        return Vector2Scale(*this, scale);
    }

    /**
     * Scale vector (multiply by value)
     */
    auto operator*=(const float scale) -> Vector2&
    {
        set(Vector2Scale(*this, scale));

        return *this;
    }

    /**
     * Divide vector by vector
     */
    inline auto Divide(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Divide(*this, vector2);
    }

    /**
     * Divide vector by vector
     */
    inline auto operator/(const ::Vector2& vector2) const -> Vector2
    {
        return Vector2Divide(*this, vector2);
    }

    /**
     * Divide vector by vector
     */
    auto operator/=(const ::Vector2& vector2) -> Vector2&
    {
        set(Vector2Divide(*this, vector2));

        return *this;
    }

    /**
     * Divide vector by value
     */
    inline auto Divide(const float div) const -> Vector2
    {
        return ::Vector2{x / div, y / div};
    }

    /**
     * Divide vector by value
     */
    inline auto operator/(const float div) const -> Vector2
    {
        return Divide(div);
    }

    /**
     * Divide vector by value
     */
    auto operator/=(const float div) -> Vector2&
    {
        this->x /= div;
        this->y /= div;

        return *this;
    }

    /**
     * Normalize provided vector
     */
    inline auto Normalize() const -> Vector2
    {
        return Vector2Normalize(*this);
    }

    /**
     * Transforms a Vector2 by a given Matrix
     */
    inline auto Transform(::Matrix mat) -> Vector2
    {
        return ::Vector2Transform(*this, mat);
    }

    /**
     * Calculate linear interpolation between two vectors
     */
    inline auto Lerp(const ::Vector2& vector2, float amount) const -> Vector2
    {
        return Vector2Lerp(*this, vector2, amount);
    }

    /**
     * Calculate reflected vector to normal
     */
    inline auto Reflect(const ::Vector2& normal) const -> Vector2
    {
        return Vector2Reflect(*this, normal);
    }

    /**
     * Rotate Vector by float in Degrees
     */
    inline auto Rotate(float degrees) const -> Vector2
    {
        return Vector2Rotate(*this, degrees);
    }

    /**
     * Move Vector towards target
     */
    inline auto MoveTowards(const ::Vector2& target, float maxDistance) const -> Vector2
    {
        return Vector2MoveTowards(*this, target, maxDistance);
    }

    /**
     * Invert the given vector
     */
    inline auto Invert() -> Vector2
    {
        return ::Vector2Invert(*this);
    }

    /**
     * Clamp the components of the vector between
     */
    inline auto Clamp(::Vector2 min, ::Vector2 max) -> Vector2
    {
        return ::Vector2Clamp(*this, min, max);
    }

    /**
     * // Clamp the magnitude of the vector between two min and max values
     */
    inline auto Clamp(float min, float max) -> Vector2
    {
        return ::Vector2ClampValue(*this, min, max);
    }

    /**
     * Check whether two given vectors are almost equal
     */
    inline auto Equals(::Vector2 q) -> int
    {
        return ::Vector2Equals(*this, q);
    }

    /**
     * Calculate vector length
     */
    inline auto Length() const -> float
    {
        return Vector2Length(*this);
    }

    /**
     * Calculate vector square length
     */
    inline auto LengthSqr() const -> float
    {
        return Vector2LengthSqr(*this);
    }

    /**
     * Calculate two vectors dot product
     */
    inline auto DotProduct(const ::Vector2& vector2) const -> float
    {
        return Vector2DotProduct(*this, vector2);
    }

    /**
     * Calculate distance between two vectors
     */
    inline auto Distance(const ::Vector2& vector2) const -> float
    {
        return Vector2Distance(*this, vector2);
    }

    /**
     * Calculate square distance between two vectors
     */
    inline auto DistanceSqr(::Vector2 v2) -> float
    {
        return ::Vector2DistanceSqr(*this, v2);
    }

    /**
     * Calculate angle from two vectors in X-axis
     */
    inline auto Angle(const ::Vector2& vector2) const -> float
    {
        return Vector2Angle(*this, vector2);
    }

    /**
     * Vector with components value 0.0f
     */
    static inline auto Zero() -> Vector2
    {
        return Vector2Zero();
    }

    /**
     * Vector with components value 1.0f
     */
    static inline auto One() -> Vector2
    {
        return Vector2One();
    }
#endif

    inline void DrawPixel(::Color color = {0, 0, 0, 255}) const {
        ::DrawPixelV(*this, color);
    }

    inline void DrawLine(::Vector2 endPos, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineV(*this, endPos, color);
    }

    inline void DrawLine(::Vector2 endPos, float thick, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineEx(*this, endPos, thick, color);
    }

    inline void DrawLineBezier(::Vector2 endPos, float thick, ::Color color = {0, 0, 0, 255}) const {
        ::DrawLineBezier(*this, endPos, thick, color);
    }

    /**
     * Draw line using quadratic bezier curves with a control point.
     */
    inline void DrawLineBezierQuad(
            ::Vector2 endPos,
            ::Vector2 controlPos,
            float thick,
            ::Color color = {0, 0, 0, 255}) const {
       ::DrawLineBezierQuad(*this, endPos, controlPos, thick, color);
    }

    /**
     * Draw a color-filled circle (Vector version)
     */
    inline void DrawCircle(float radius, ::Color color = {0, 0, 0, 255}) const {
        ::DrawCircleV(*this, radius, color);
    }

    inline void DrawRectangle(::Vector2 size, ::Color color = {0, 0, 0, 255}) const {
        ::DrawRectangleV(*this, size, color);
    }

    inline void DrawPoly(int sides, float radius, float rotation, ::Color color = {0, 0, 0, 255}) const {
        ::DrawPoly(*this, sides, radius, rotation, color);
    }

    /**
     * Check collision between two circles
     */
    inline auto CheckCollisionCircle(float radius1, ::Vector2 center2, float radius2) const -> bool
    {
        return ::CheckCollisionCircles(*this, radius1, center2, radius2);
    }

    /**
     * Check collision between circle and rectangle
     */
    inline auto CheckCollisionCircle(float radius, ::Rectangle rec) const -> bool
    {
        return ::CheckCollisionCircleRec(*this, radius, rec);
    }

    /**
     * Check if point is inside rectangle
     */
    inline auto CheckCollision(::Rectangle rec) const -> bool
    {
        return ::CheckCollisionPointRec(*this, rec);
    }

    /**
     * Check if point is inside circle
     */
    inline auto CheckCollision(::Vector2 center, float radius) const -> bool
    {
        return ::CheckCollisionPointCircle(*this, center, radius);
    }

    /**
     * Check if point is inside a triangle
     */
    inline auto CheckCollision(::Vector2 p1, ::Vector2 p2, ::Vector2 p3) const -> bool
    {
        return ::CheckCollisionPointTriangle(*this, p1, p2, p3);
    }

    /**
     * Check the collision between two lines defined by two points each, returns collision point by reference
     */
    inline auto CheckCollisionLines(
        ::Vector2 endPos1,
        ::Vector2 startPos2, ::Vector2 endPos2,
        ::Vector2* collisionPoint) const -> bool
    {
        return ::CheckCollisionLines(*this, endPos1, startPos2, endPos2, collisionPoint);
    }

    /**
     * Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
     */
    inline auto CheckCollisionPointLine(::Vector2 p1, ::Vector2 p2, int threshold = 1) -> bool
    {
        return ::CheckCollisionPointLine(*this, p1, p2, threshold);
    }

 private:
    void set(const ::Vector2& vec) {
        x = vec.x;
        y = vec.y;
    }
};

}  // namespace raylib

using RVector2 = raylib::Vector2;

#endif  // RAYLIB_CPP_INCLUDE_VECTOR2_HPP_
