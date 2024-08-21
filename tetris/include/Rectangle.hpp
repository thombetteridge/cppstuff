#ifndef RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
#define RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./Vector2.hpp"

namespace raylib {
/**
 * Rectangle type
 */
class Rectangle : public ::Rectangle {
 public:
    Rectangle(const ::Rectangle& rect) : ::Rectangle{rect.x, rect.y, rect.width, rect.height} {}

    Rectangle(float x, float y, float width, float height) : ::Rectangle{x, y, width, height} {}
    Rectangle(float x, float y, float width) : ::Rectangle{x, y, width, 0} {}
    Rectangle(float x, float y) : ::Rectangle{x, y, 0, 0} {}
    Rectangle(float x) : ::Rectangle{x, 0, 0, 0} {}
    Rectangle() : ::Rectangle{0, 0, 0, 0} {}

    Rectangle(::Vector2 position, ::Vector2 size)
            : ::Rectangle{position.x, position.y, size.x, size.y} {}
    Rectangle(::Vector2 size) : ::Rectangle{0, 0, size.x, size.y} {}
    Rectangle(::Vector4 rect) : ::Rectangle{rect.x, rect.y, rect.z, rect.w} {}

    GETTERSETTER(float, X, x)
    GETTERSETTER(float, Y, y)
    GETTERSETTER(float, Width, width)
    GETTERSETTER(float, Height, height)

    auto operator=(const ::Rectangle& rect) -> Rectangle&
    {
        set(rect);
        return *this;
    }

    inline auto ToVector4() -> ::Vector4
    {
        return {x, y, width, height};
    }

    operator ::Vector4() const {
        return {x, y, width, height};
    }

    /**
     * Draw a color-filled rectangle
     */
    inline void Draw(::Color color) const {
        ::DrawRectangleRec(*this, color);
    }

    inline void Draw(::Vector2 origin, float rotation, ::Color color) const {
        ::DrawRectanglePro(*this, origin, rotation, color);
    }

    inline void DrawGradientV(::Color color1, ::Color color2) const {
        ::DrawRectangleGradientV(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color1, color2);
    }

    inline void DrawGradientH(::Color color1, ::Color color2) const {
        ::DrawRectangleGradientH(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color1, color2);
    }

    inline void DrawGradient(::Color col1, ::Color col2, ::Color col3, ::Color col4) const {
        ::DrawRectangleGradientEx(*this, col1, col2, col3, col4);
    }

    inline void DrawLines(::Color color) const {
        ::DrawRectangleLines(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
            static_cast<int>(height), color);
    }

    inline void DrawLines(::Color color, float lineThick) const {
        ::DrawRectangleLinesEx(*this, lineThick, color);
    }

    inline void DrawRounded(float roundness, int segments, ::Color color) const {
        ::DrawRectangleRounded(*this, roundness, segments, color);
    }

    inline void DrawRoundedLines(float roundness, int segments,
            float lineThick, ::Color color) const {
        ::DrawRectangleRoundedLines(*this, roundness, segments, lineThick, color);
    }

    /**
     * Check collision between two rectangles
     */
    inline auto CheckCollision(::Rectangle rec2) const -> bool
    {
        return ::CheckCollisionRecs(*this, rec2);
    }

    /**
     * Get collision rectangle for two rectangles collision
     */
    inline auto GetCollision(::Rectangle rec2) const -> ::Rectangle
    {
        return ::GetCollisionRec(*this, rec2);
    }

    /**
     * Check if point is inside rectangle
     */
    inline auto CheckCollision(::Vector2 point) const -> bool
    {
        return ::CheckCollisionPointRec(point, *this);
    }

    /**
     * Check collision between circle and rectangle
     */
    inline auto CheckCollision(::Vector2 center, float radius) -> bool
    {
        return ::CheckCollisionCircleRec(center, radius, *this);
    }

    inline auto GetSize() -> Vector2
    {
        return {width, height};
    }

    inline auto SetSize(float newWidth, float newHeight) -> Rectangle&
    {
        width = newWidth;
        height = newHeight;
        return *this;
    }

    inline auto SetSize(const ::Vector2& size) -> Rectangle&
    {
        return SetSize(size.x, size.y);
    }

    inline auto SetShapesTexture(const ::Texture2D& texture) -> Rectangle&
    {
        ::SetShapesTexture(texture, *this);
        return *this;
    }

    inline auto GetPosition() -> Vector2
    {
        return {x, y};
    }

    inline auto SetPosition(float newX, float newY) -> Rectangle&
    {
        x = newX;
        y = newY;
        return *this;
    }

    inline auto SetPosition(const ::Vector2& position) -> Rectangle&
    {
        return SetPosition(position.x, position.y);
    }

 private:
    void set(const ::Rectangle& rect) {
        x = rect.x;
        y = rect.y;
        width = rect.width;
        height = rect.height;
    }
};
}  // namespace raylib

using RRectangle = raylib::Rectangle;

#endif  // RAYLIB_CPP_INCLUDE_RECTANGLE_HPP_
