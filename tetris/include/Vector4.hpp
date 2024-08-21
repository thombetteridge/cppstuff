#ifndef RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
#define RAYLIB_CPP_INCLUDE_VECTOR4_HPP_

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#include <utility>
#endif

#include "./raylib.hpp"
#include "./raymath.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Vector4 type
 */
class Vector4 : public ::Vector4 {
 public:
    Vector4(const ::Vector4& vec) : ::Vector4{vec.x, vec.y, vec.z, vec.w} {}

    Vector4(float x, float y, float z, float w) : ::Vector4{x, y, z, w} {}
    Vector4(float x, float y, float z) : ::Vector4{x, y, z, 0} {}
    Vector4(float x, float y) : ::Vector4{x, y, 0, 0} {}
    Vector4(float x) : ::Vector4{x, 0, 0, 0} {}
    Vector4() : ::Vector4{0, 0, 0, 0} {}
    Vector4(::Rectangle rectangle) : ::Vector4{rectangle.x, rectangle.y, rectangle.width, rectangle.height} {}

    Vector4(::Color color) {
        set(ColorNormalize(color));
    }

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Z, z)
    GETTERSETTER(float, W, w)

    auto operator=(const ::Vector4& vector4) -> Vector4&
    {
        set(vector4);
        return *this;
    }

    auto operator==(const ::Vector4& other) -> bool
    {
        return x == other.x
            && y == other.y
            && z == other.z
            && w == other.w;
    }

    auto operator!=(const ::Vector4& other) -> bool
    {
        return !(*this == other);
    }

    inline auto ToRectangle() -> ::Rectangle
    {
        return {x, y, z, w};
    }

    operator ::Rectangle() const {
        return {x, y, z, w};
    }

#ifndef RAYLIB_CPP_NO_MATH
    inline auto Multiply(const ::Vector4& vector4) const -> Vector4
    {
        return QuaternionMultiply(*this, vector4);
    }

    inline auto operator*(const ::Vector4& vector4) const -> Vector4
    {
        return QuaternionMultiply(*this, vector4);
    }

    inline auto Lerp(const ::Vector4& vector4, float amount) const -> Vector4
    {
        return QuaternionLerp(*this, vector4, amount);
    }

    inline auto Nlerp(const ::Vector4& vector4, float amount) const -> Vector4
    {
        return QuaternionNlerp(*this, vector4, amount);
    }

    inline auto Slerp(const ::Vector4& vector4, float amount) const -> Vector4
    {
        return QuaternionSlerp(*this, vector4, amount);
    }

    inline auto ToMatrix() const -> Matrix
    {
        return QuaternionToMatrix(*this);
    }

    inline auto Length() const -> float
    {
        return QuaternionLength(*this);
    }

    inline auto Normalize() const -> Vector4
    {
        return QuaternionNormalize(*this);
    }

    inline auto Invert() const -> Vector4
    {
        return QuaternionInvert(*this);
    }

    inline void ToAxisAngle(::Vector3 *outAxis, float *outAngle) {
        QuaternionToAxisAngle(*this, outAxis, outAngle);
    }

    /**
     * Get the rotation angle and axis for a given quaternion
     */
    auto ToAxisAngle() -> std::pair<Vector3, float>
    {
        Vector3 outAxis;
        float outAngle;
        QuaternionToAxisAngle(*this, &outAxis, &outAngle);

        return std::pair<Vector3, float>(outAxis, outAngle);
    }

    inline auto Transform(const ::Matrix& matrix) -> Vector4
    {
        return ::QuaternionTransform(*this, matrix);
    }

    static inline auto Identity() -> Vector4
    {
        return ::QuaternionIdentity();
    }

    static inline auto FromVector3ToVector3(const ::Vector3& from, const ::Vector3& to) -> Vector4
    {
        return ::QuaternionFromVector3ToVector3(from , to);
    }

    static inline auto FromMatrix(const ::Matrix& matrix) -> Vector4
    {
        return ::QuaternionFromMatrix(matrix);
    }

    static inline auto FromAxisAngle(const ::Vector3& axis, const float angle) -> Vector4
    {
        return ::QuaternionFromAxisAngle(axis, angle);
    }

    static inline auto FromEuler(const float yaw, const float pitch, const float roll) -> Vector4
    {
        return ::QuaternionFromEuler(yaw, pitch, roll);
    }

    static inline auto FromEuler(const ::Vector3& vector3) -> Vector4
    {
        return ::QuaternionFromEuler(vector3.x, vector3.y, vector3.z);
    }

    inline auto ToEuler() -> Vector3
    {
        return ::QuaternionToEuler(*this);
    }
#endif

    inline auto ColorFromNormalized() const -> Color
    {
        return ::ColorFromNormalized(*this);
    }

    operator Color() {
        return ColorFromNormalized();
    }

 private:
    void set(const ::Vector4& vec4) {
        x = vec4.x;
        y = vec4.y;
        z = vec4.z;
        w = vec4.w;
    }
};

// Alias the Vector4 as Quaternion.
typedef Vector4 Quaternion;
}  // namespace raylib

using RVector4 = raylib::Vector4;
using RQuaternion = raylib::Quaternion;

#endif  // RAYLIB_CPP_INCLUDE_VECTOR4_HPP_
