#ifndef RAYLIB_CPP_INCLUDE_MATRIX_HPP_
#define RAYLIB_CPP_INCLUDE_MATRIX_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./raymath.hpp"

#ifndef RAYLIB_CPP_NO_MATH
#include <cmath>
#endif

namespace raylib {
/**
 * Matrix type (OpenGL style 4x4 - right handed, column major)
 */
class Matrix : public ::Matrix {
 public:
    Matrix(const ::Matrix& mat) : ::Matrix{
            mat.m0, mat.m4, mat.m8, mat.m12,
            mat.m1, mat.m5, mat.m9, mat.m13,
            mat.m2, mat.m6, mat.m10, mat.m14,
            mat.m3, mat.m7, mat.m11, mat.m15} {
        // Nothing.
    }

    Matrix(
            float m0 = 0, float m4 = 0, float m8 = 0, float m12 = 0,
            float m1 = 0, float m5 = 0, float m9 = 0, float m13 = 0,
            float m2 = 0, float m6 = 0, float m10 = 0, float m14 = 0,
            float m3 = 0, float m7 = 0, float m11 = 0, float m15 = 0) :
        ::Matrix{
            m0, m4, m8, m12,
            m1, m5, m9, m13,
            m2, m6, m10, m14,
            m3, m7, m11, m15} {
        // Nothing.
    }

    GETTERSETTER(float, M0, m0)
    GETTERSETTER(float, M1, m1)
    GETTERSETTER(float, M2, m2)
    GETTERSETTER(float, M3, m3)
    GETTERSETTER(float, M4, m4)
    GETTERSETTER(float, M5, m5)
    GETTERSETTER(float, M6, m6)
    GETTERSETTER(float, M7, m7)
    GETTERSETTER(float, M8, m8)
    GETTERSETTER(float, M9, m9)
    GETTERSETTER(float, M10, m10)
    GETTERSETTER(float, M11, m11)
    GETTERSETTER(float, M12, m12)
    GETTERSETTER(float, M13, m13)
    GETTERSETTER(float, M14, m14)
    GETTERSETTER(float, M15, m15)

    auto operator=(const ::Matrix& matrix) -> Matrix&
    {
        set(matrix);
        return *this;
    }

    auto operator=(const Matrix& matrix) -> Matrix&
    {
        set(matrix);
        return *this;
    }

    auto operator==(const ::Matrix& other) -> bool
    {
        return m0 == other.m0
            && m1 == other.m1
            && m2 == other.m2
            && m3 == other.m3
            && m4 == other.m4
            && m5 == other.m5
            && m6 == other.m6
            && m7 == other.m7
            && m8 == other.m8
            && m9 == other.m9
            && m10 == other.m10
            && m11 == other.m11
            && m12 == other.m12
            && m13 == other.m13
            && m14 == other.m14
            && m15 == other.m15;
    }

    auto operator!=(const ::Matrix& other) -> bool
    {
        return !(*this == other);
    }

#ifndef RAYLIB_CPP_NO_MATH
    /**
     * Returns the trace of the matrix (sum of the values along the diagonal)
     */
    inline auto Trace() const -> float
    {
        return ::MatrixTrace(*this);
    }

    /**
     * Transposes provided matrix
     */
    inline auto Transpose() const -> Matrix
    {
        return ::MatrixTranspose(*this);
    }

    inline auto Invert() const -> Matrix
    {
        return ::MatrixInvert(*this);
    }

    static auto Identity() -> Matrix
    {
        return ::MatrixIdentity();
    }

    auto Add(const ::Matrix& right) -> Matrix
    {
        return ::MatrixAdd(*this, right);
    }

    auto operator+(const ::Matrix& matrix) -> Matrix
    {
        return ::MatrixAdd(*this, matrix);
    }

    auto Subtract(const ::Matrix& right) -> Matrix
    {
        return ::MatrixSubtract(*this, right);
    }

    auto operator-(const ::Matrix& matrix) -> Matrix
    {
        return ::MatrixSubtract(*this, matrix);
    }

    static auto Translate(float x, float y, float z) -> Matrix
    {
        return ::MatrixTranslate(x, y, z);
    }

    static auto Rotate(Vector3 axis, float angle) -> Matrix
    {
        return ::MatrixRotate(axis, angle);
    }

    static auto RotateXYZ(Vector3 angle) -> Matrix
    {
        return ::MatrixRotateXYZ(angle);
    }

    static auto RotateX(float angle) -> Matrix
    {
        return ::MatrixRotateX(angle);
    }

    static auto RotateY(float angle) -> Matrix
    {
        return ::MatrixRotateY(angle);
    }

    static auto RotateZ(float angle) -> Matrix
    {
        return ::MatrixRotateZ(angle);
    }

    static auto Scale(float x, float y, float z) -> Matrix
    {
        return ::MatrixScale(x, y, z);
    }

    auto Multiply(const ::Matrix& right) const -> Matrix
    {
        return ::MatrixMultiply(*this, right);
    }

    auto operator*(const ::Matrix& matrix) -> Matrix
    {
        return ::MatrixMultiply(*this, matrix);
    }

    static auto Frustum(double left, double right, double bottom, double top,
        double near, double far) -> Matrix
    {
        return ::MatrixFrustum(left, right, bottom, top, near, far);
    }

    static auto Perspective(double fovy, double aspect, double near, double far) -> Matrix
    {
        return ::MatrixPerspective(fovy, aspect, near, far);
    }

    static auto Ortho(double left, double right, double bottom, double top,
        double near, double far) -> Matrix
    {
        return ::MatrixOrtho(left, right, bottom, top, near, far);
    }

    static auto LookAt(Vector3 eye, Vector3 target, Vector3 up) -> Matrix
    {
        return ::MatrixLookAt(eye, target, up);
    }

    inline auto ToFloatV() const -> float16
    {
        return ::MatrixToFloatV(*this);
    }

    operator float16() {
        return ToFloatV();
    }

    /**
     * Set shader uniform value (matrix 4x4)
     */
    inline auto SetShaderValue(const ::Shader& shader, int uniformLoc) -> Matrix&
    {
        ::SetShaderValueMatrix(shader, uniformLoc, *this);
        return *this;
    }

    inline static auto GetCamera(const ::Camera& camera) -> Matrix
    {
        return ::GetCameraMatrix(camera);
    }

    inline static auto GetCamera(const ::Camera2D& camera) -> Matrix
    {
        return ::GetCameraMatrix2D(camera);
    }

#endif

 private:
    void set(const ::Matrix& mat) {
        m0 = mat.m0;
        m1 = mat.m1;
        m2 = mat.m2;
        m3 = mat.m3;
        m4 = mat.m4;
        m5 = mat.m5;
        m6 = mat.m6;
        m7 = mat.m7;
        m8 = mat.m8;
        m9 = mat.m9;
        m10 = mat.m10;
        m11 = mat.m11;
        m12 = mat.m12;
        m13 = mat.m13;
        m14 = mat.m14;
        m15 = mat.m15;
    }
};
}  // namespace raylib

using RMatrix = raylib::Matrix;

#endif  // RAYLIB_CPP_INCLUDE_MATRIX_HPP_
