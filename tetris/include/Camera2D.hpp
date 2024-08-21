#ifndef RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
#define RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_

#include "./raylib.hpp"
#include "./Vector2.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Camera2D type, defines a 2d camera
 */
class Camera2D : public ::Camera2D {
 public:
    Camera2D(const ::Camera2D& camera) {
        set(camera);
    }

    Camera2D() {}
    Camera2D(::Vector2 offset, ::Vector2 target,
            float rotation = 0.0f, float zoom = 1.0f) : ::Camera2D{offset, target, rotation, zoom} {}

    inline auto BeginMode() -> Camera2D&
    {
        ::BeginMode2D(*this);
        return *this;
    }

    inline auto EndMode() -> Camera2D&
    {
        ::EndMode2D();
        return *this;
    }

    GETTERSETTER(::Vector2, Offset, offset)
    GETTERSETTER(::Vector2, Target, target)
    GETTERSETTER(float, Rotation, rotation)
    GETTERSETTER(float, Zoom, zoom)

    auto operator=(const ::Camera2D& camera) -> Camera2D&
    {
        set(camera);
        return *this;
    }

    /**
     * Returns camera 2d transform matrix
     */
    inline auto GetMatrix() const -> Matrix
    {
        return ::GetCameraMatrix2D(*this);
    }

    /**
     * Returns the world space position for a 2d camera screen space position
     */
    inline auto GetScreenToWorld(::Vector2 position) const -> Vector2
    {
        return ::GetScreenToWorld2D(position, *this);
    }

    /**
     * Returns the screen space position for a 3d world space position
     */
    inline auto GetWorldToScreen(::Vector2 position) const -> Vector2
    {
        return ::GetWorldToScreen2D(position, *this);
    }

 private:
    void set(const ::Camera2D& camera) {
        offset = camera.offset;
        target = camera.target;
        rotation = camera.rotation;
        zoom = camera.zoom;
    }
};
}  // namespace raylib

using RCamera2D = raylib::Camera2D;

#endif  // RAYLIB_CPP_INCLUDE_CAMERA2D_HPP_
