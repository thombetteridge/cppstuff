
#ifndef RAYLIB_CPP_INCLUDE_COLOR_HPP_
#define RAYLIB_CPP_INCLUDE_COLOR_HPP_

#include <string>

#include "./raylib.hpp"
#include "./Vector4.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Color type, RGBA (32bit)
 */
class Color : public ::Color {
 public:
    Color(const ::Color& color) : ::Color{color.r, color.g, color.b, color.a} {}

    Color(
            unsigned char red,
            unsigned char green,
            unsigned char blue,
            unsigned char alpha = 255) : ::Color{red, green, blue, alpha} {};

    /**
     * Black.
     */
    Color() : ::Color{0, 0, 0, 255} {};

    /**
     * Returns a Color from HSV values
     */
    Color(::Vector3 hsv) {
        set(::ColorFromHSV(hsv.x, hsv.y, hsv.z));
    }

    /**
     * Returns a Color from HSV values
     */
    {
        return ::ColorFromHSV(hue, saturation, value);
    }

    /**
     * Get Color structure from hexadecimal value
     */
    Color(unsigned int hexValue) {
        set(::GetColor(hexValue));
    }

    Color(void *srcPtr, int format) {
        set(::GetPixelColor(srcPtr, format));
    }

    /**
     * Returns hexadecimal value for a Color
     */
    auto ToInt() const -> int
    {
        return ::ColorToInt(*this);
    }

    /**
     * Returns hexadecimal value for a Color
     */
    operator int() const {
        return ::ColorToInt(*this);
    }

    /**
     * Returns color with alpha applied, alpha goes from 0.0f to 1.0f
     */
    auto Fade(float alpha) const -> Color
    {
        return ::Fade(*this, alpha);
    }

    /**
     * Returns Color normalized as float [0..1]
     */
    auto Normalize() const -> Vector4
    {
        return ::ColorNormalize(*this);
    }

    /**
     * Returns Color from normalized values [0..1]
     */
    Color(::Vector4 normalized) {
        set(::ColorFromNormalized(normalized));
    }

    /**
     * Returns HSV values for a Color
     */
    auto ToHSV() const -> Vector3
    {
        return ::ColorToHSV(*this);
    }

    GETTERSETTER(unsigned char, R, r)
    GETTERSETTER(unsigned char, G, g)
    GETTERSETTER(unsigned char, B, b)
    GETTERSETTER(unsigned char, A, a)

    auto operator=(const ::Color& color) -> Color&
    {
        set(color);
        return *this;
    }

    /**
     * Set background color (framebuffer clear color)
     */
    inline auto ClearBackground() -> Color&
    {
        ::ClearBackground(*this);
        return *this;
    }

    inline void DrawPixel(int x, int y) const {
        ::DrawPixel(x, y, *this);
    }

    /**
     * Draw a pixel
     */
    inline void DrawPixel(::Vector2 pos) const {
        ::DrawPixelV(pos, *this);
    }

    /**
     * Draw a line
     */
    inline void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY) const {
        ::DrawLine(startPosX, startPosY, endPosX, endPosY, *this);
    }

    /**
     * Draw a line using Vector points
     */
    inline void DrawLine(::Vector2 startPos, ::Vector2 endPos) const {
        ::DrawLineV(startPos, endPos, *this);
    }

    /**
     * Draw a line using Vector points, with a given thickness
     */
    inline void DrawLine(::Vector2 startPos, ::Vector2 endPos, float thick) const {
        ::DrawLineEx(startPos, endPos, thick, *this);
    }

    inline void DrawLineBezier(::Vector2 startPos, ::Vector2 endPos, float thick = 1.0f) const {
        ::DrawLineBezier(startPos, endPos, thick, *this);
    }

    inline void DrawLineStrip(::Vector2 *points, int numPoints) const {
        ::DrawLineStrip(points, numPoints, *this);
    }

    inline void DrawText(const std::string& text, int posX = 0, int posY = 0, int fontSize = 10.0f) const {
        ::DrawText(text.c_str(), posX, posY, fontSize, *this);
    }

    inline void DrawText(const ::Font& font, const std::string& text, ::Vector2 position,
            float fontSize, float spacing) const {
        ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, *this);
    }

    inline void DrawText(
            const ::Font& font,
            const std::string& text,
            ::Vector2 position,
            ::Vector2 origin,
            float rotation,
            float fontSize,
            float spacing) const {
        ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, *this);
    }

    inline void DrawRectangle(int posX, int posY, int width, int height) const {
        ::DrawRectangle(posX, posY, width, height, *this);
    }

    inline void DrawRectangle(::Vector2 position, ::Vector2 size) const {
        ::DrawRectangleV(position, size, *this);
    }

    inline void DrawRectangle(::Rectangle rec) const {
        ::DrawRectangleRec(rec, *this);
    }

    inline void DrawRectangle(::Rectangle rec, ::Vector2 origin, float rotation) const {
        ::DrawRectanglePro(rec, origin, rotation, *this);
    }

    inline void DrawRectangleLines(int posX, int posY, int width, int height) const {
        ::DrawRectangleLines(posX, posY, width, height, *this);
    }

    inline void DrawRectangleLines(::Rectangle rec, float lineThick) const {
        ::DrawRectangleLinesEx(rec, lineThick, *this);
    }

    /**
     * Returns color with alpha applied, alpha goes from 0.0f to 1.0f
     */
    auto Alpha(float alpha) const -> Color
    {
        return ::ColorAlpha(*this, alpha);
    }

    /**
     * Returns src alpha-blended into dst color with tint
     */
    auto AlphaBlend(::Color dst, ::Color tint) const -> Color
    {
        return ::ColorAlphaBlend(dst, *this, tint);
    }

    inline static auto LightGray() -> Color { return LIGHTGRAY; }
    inline static auto Gray() -> Color { return GRAY; }
    inline static auto DarkGray() -> Color { return DARKGRAY; }
    inline static auto Yellow() -> Color { return YELLOW; }
    inline static auto Gold() -> Color { return GOLD; }
    inline static auto Orange() -> Color { return ORANGE; }
    inline static auto Pink() -> Color { return PINK; }
    inline static auto Red() -> Color { return RED; }
    inline static auto Maroon() -> Color { return MAROON; }
    inline static auto Green() -> Color { return GREEN; }
    inline static auto Lime() -> Color { return LIME; }
    inline static auto DarkGreen() -> Color { return DARKGREEN; }
    inline static auto SkyBlue() -> Color { return SKYBLUE; }
    inline static auto Blue() -> Color { return BLUE; }
    inline static auto DarkBlue() -> Color { return DARKBLUE; }
    inline static auto Purple() -> Color { return PURPLE; }
    inline static auto Violet() -> Color { return VIOLET; }
    inline static auto DarkPurple() -> Color { return DARKPURPLE; }
    inline static auto Beige() -> Color { return BEIGE; }
    inline static auto Brown() -> Color { return BROWN; }
    inline static auto DarkBrown() -> Color { return DARKBROWN; }
    inline static auto White() -> Color { return WHITE; }
    inline static auto Black() -> Color { return BLACK; }
    inline static auto Blank() -> Color { return BLANK; }
    inline static auto Magenta() -> Color { return MAGENTA; }
    inline static auto RayWhite() -> Color { return RAYWHITE; }

private:
 private:
    void set(const ::Color& color) {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }
};

}  // namespace raylib

using RColor = raylib::Color;

#endif  // RAYLIB_CPP_INCLUDE_COLOR_HPP_
