#ifndef RAYLIB_CPP_INCLUDE_SHADER_HPP_
#define RAYLIB_CPP_INCLUDE_SHADER_HPP_

#include <string>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "Texture.hpp"

namespace raylib {
/**
 * Shader type (generic)
 */
class Shader : public ::Shader {
 public:
    Shader(const ::Shader& shader) {
        set(shader);
    }

    Shader(unsigned int id, int* locs = nullptr) : ::Shader{id, locs} {}

    Shader(const std::string& vsFileName, const std::string& fsFileName) {
        set(::LoadShader(vsFileName.c_str(), fsFileName.c_str()));
    }

    Shader(const char* vsFileName, const char* fsFileName) {
        set(::LoadShader(vsFileName, fsFileName));
    }

    Shader(const Shader&) = delete;

    Shader(Shader&& other) {
        set(other);

        other.id = 0;
        other.locs = nullptr;
    }

    /**
     * Load shader from files and bind default locations.
     *
     * @see ::LoadShader
     */
    static auto Load(const std::string& vsFileName, const std::string& fsFileName) -> ::Shader
    {
        return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
    }

    /**
     * Load a shader from memory.
     *
     * @see ::LoadShaderFromMemory
     */
    static auto LoadFromMemory(const std::string& vsCode, const std::string& fsCode) -> ::Shader
    {
        return ::LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
    }

    GETTERSETTER(unsigned int, Id, id)
    GETTERSETTER(int*, Locs, locs)

    auto operator=(const ::Shader& shader) -> Shader&
    {
        set(shader);
        return *this;
    }

    auto operator=(const Shader&) -> Shader& = delete;

    auto operator=(Shader&& other) noexcept -> Shader&
    {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.id = 0;
        other.locs = nullptr;

        return *this;
    }

    /**
     * Unload shader from GPU memory (VRAM)
     */
    ~Shader() {
        Unload();
    }

    /**
     * Unload shader from GPU memory (VRAM)
     */
    void Unload() {
        if (locs != nullptr) {
            ::UnloadShader(*this);
        }
    }

    /**
     * Begin custom shader drawing.
     */
    inline auto BeginMode() -> Shader&
    {
        ::BeginShaderMode(*this);
        return *this;
    }

    /**
     * End custom shader drawing (use default shader).
     */
    inline auto EndMode() -> Shader&
    {
        ::EndShaderMode();
        return *this;
    }

    /**
     * Get shader uniform location
     *
     * @see GetShaderLocation()
     */
    inline auto GetLocation(const std::string& uniformName) const -> int
    {
        return ::GetShaderLocation(*this, uniformName.c_str());
    }

    /**
     * Get shader attribute location
     *
     * @see GetShaderLocationAttrib()
     */
    inline auto GetLocationAttrib(const std::string& attribName) const -> int
    {
        return ::GetShaderLocationAttrib(*this, attribName.c_str());
    }

    /**
     * Set shader uniform value
     *
     * @see SetShaderValue()
     */
    inline auto SetValue(int uniformLoc, const void* value, int uniformType) -> Shader&
    {
        ::SetShaderValue(*this, uniformLoc, value, uniformType);
        return *this;
    }

    /**
     * Set shader uniform value vector
     *
     * @see SetShaderValueV()
     */
    inline auto SetValue(int uniformLoc, const void* value, int uniformType, int count) -> Shader&
    {
        ::SetShaderValueV(*this, uniformLoc, value, uniformType, count);
        return *this;
    }

    /**
     * Set shader uniform value (matrix 4x4)
     *
     * @see SetShaderValueMatrix()
     */
    inline auto SetValue(int uniformLoc, const ::Matrix& mat) -> Shader&
    {
        ::SetShaderValueMatrix(*this, uniformLoc, mat);
        return *this;
    }

    /**
     * Set shader uniform value for texture
     *
     * @see SetShaderValueTexture()
     */
    inline auto SetValue(int uniformLoc, const ::Texture2D& texture) -> Shader&
    {
        ::SetShaderValueTexture(*this, uniformLoc, texture);
        return *this;
    }

    /**
     * Retrieves whether or not the shader is ready.
     */
    auto IsReady() const -> bool
    {
        return id != 0 && locs != nullptr;
    }

 private:
    void set(const ::Shader& shader) {
        id = shader.id;
        locs = shader.locs;
    }
};
}  // namespace raylib

using RShader = raylib::Shader;

#endif  // RAYLIB_CPP_INCLUDE_SHADER_HPP_
