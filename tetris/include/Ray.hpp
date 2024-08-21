#ifndef RAYLIB_CPP_INCLUDE_RAY_HPP_
#define RAYLIB_CPP_INCLUDE_RAY_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RayCollision.hpp"

namespace raylib {
/**
 * Ray type (useful for raycast)
 */
class Ray : public ::Ray {
 public:
    Ray(const ::Ray& ray) {
        set(ray);
    }

    Ray(::Vector3 position = {0.0f, 0.0f, 0.0f}, ::Vector3 direction = {0.0f, 0.0f, 0.0f}) :
            ::Ray{position, direction} {
        // Nothing.
    }

    Ray(::Vector2 mousePosition, const ::Camera& camera) {
        set(::GetMouseRay(mousePosition, camera));
    }

    auto operator=(const ::Ray& ray) -> Ray&
    {
        set(ray);
        return *this;
    }

    GETTERSETTER(::Vector3, Position, position)
    GETTERSETTER(::Vector3, Direction, direction)

    /**
     * Draw a ray line
     */
    inline void Draw(::Color color) const {
        DrawRay(*this, color);
    }

    /**
     * Get collision information between ray and sphere
     */
    inline auto GetCollision(::Vector3 center, float radius) const -> RayCollision
    {
        return ::GetRayCollisionSphere(*this, center, radius);
    }

    /**
     * Detect collision between ray and box
     */
    inline auto GetCollision(const ::BoundingBox& box) const -> RayCollision
    {
        return ::GetRayCollisionBox(*this, box);
    }

    /**
     * Get collision information between ray and mesh
     */
    inline auto GetCollision(const ::Mesh& mesh, const ::Matrix& transform) const -> RayCollision
    {
        return ::GetRayCollisionMesh(*this, mesh, transform);
    }

    /**
     * Get collision info between ray and triangle
     */
    inline auto GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3) const -> RayCollision
    {
        return ::GetRayCollisionTriangle(*this, p1, p2, p3);
    }

    /**
     * Get collision info between ray and quad
     */
    inline auto GetCollision(::Vector3 p1, ::Vector3 p2, ::Vector3 p3, ::Vector3 p4) const -> RayCollision
    {
        return ::GetRayCollisionQuad(*this, p1, p2, p3, p4);
    }

    /**
     * Get a ray trace from mouse position
     */
    inline static auto GetMouse(::Vector2 mousePosition, const ::Camera& camera) -> Ray
    {
        return ::GetMouseRay(mousePosition, camera);
    }

    /**
     * Get a ray trace from mouse position
     */
    inline static auto GetMouse(const ::Camera& camera) -> Ray
    {
        return ::GetMouseRay(::GetMousePosition(), camera);
    }

 private:
    inline void set(const ::Ray& ray) {
        position = ray.position;
        direction = ray.direction;
    }
};
}  // namespace raylib

using RRay = raylib::Ray;

#endif  // RAYLIB_CPP_INCLUDE_RAY_HPP_
