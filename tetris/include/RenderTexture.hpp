#ifndef RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
#define RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./RaylibException.hpp"
#include "./TextureUnmanaged.hpp"

namespace raylib {
/**
 * RenderTexture type, for texture rendering
 */
class RenderTexture : public ::RenderTexture {
 public:
    /**
     * Default constructor to build an empty RenderTexture.
     */
    RenderTexture() {
        id = 0;
    }

    RenderTexture(const ::RenderTexture& renderTexture) {
        set(renderTexture);
    }

    RenderTexture(unsigned int id, const ::Texture& texture, const ::Texture& depth) :
        ::RenderTexture{id, texture, depth} {}

    /**
     * Load texture for rendering (framebuffer)
     */
    RenderTexture(int width, int height) {
        set(::LoadRenderTexture(width, height));
    }

    RenderTexture(const RenderTexture&) = delete;

    RenderTexture(RenderTexture&& other) {
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};
    }

    GETTERSETTER(unsigned int, Id, id)

    /**
     * Get the color buffer attachment texture.
     */
    inline auto GetTexture() -> TextureUnmanaged
    {
        return texture;
    }

    inline void SetTexture(const ::Texture& newTexture) {
        texture = newTexture;
    }

    /**
     * Depth buffer attachment texture
     */
    inline auto GetDepth() -> TextureUnmanaged
    {
        return depth;
    }

    inline void SetDepth(const ::Texture& newDepth) {
        depth = newDepth;
    }

    auto operator=(const ::RenderTexture& texture) -> RenderTexture&
    {
        set(texture);
        return *this;
    }

    auto operator=(const RenderTexture&) -> RenderTexture& = delete;

    auto operator=(RenderTexture&& other) noexcept -> RenderTexture&
    {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.texture = {};
        other.depth = {};

        return *this;
    }

    ~RenderTexture() {
        Unload();
    }

    inline void Unload() {
        UnloadRenderTexture(*this);
    }

    /**
     * Initializes render texture for drawing
     */
    inline auto BeginMode() -> RenderTexture&
    {
        ::BeginTextureMode(*this);
        return *this;
    }

    /**
     * Ends drawing to render texture
     */
    inline auto EndMode() -> RenderTexture&
    {
        ::EndTextureMode();
        return *this;
    }

    /**
     * Load texture for rendering (framebuffer)
     */
    static auto Load(int width, int height) -> RenderTexture
    {
        return ::LoadRenderTexture(width, height);
    }

    /**
     * Retrieves whether or not the render texture is ready.
     */
    inline auto IsReady() const -> bool
    {
        return ::IsRenderTextureReady(*this);
    }

 private:
    void set(const ::RenderTexture& renderTexture) {
        id = renderTexture.id;
        texture = renderTexture.texture;
        depth = renderTexture.depth;
    }
};
typedef RenderTexture RenderTexture2D;
}  // namespace raylib

using RRenderTexture = raylib::RenderTexture;
using RRenderTexture2D = raylib::RenderTexture2D;

#endif  // RAYLIB_CPP_INCLUDE_RENDERTEXTURE_HPP_
