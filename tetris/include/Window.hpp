#ifndef RAYLIB_CPP_INCLUDE_WINDOW_HPP_
#define RAYLIB_CPP_INCLUDE_WINDOW_HPP_

#include <string>

#include "./raylib.hpp"
#include "./RaylibException.hpp"
#include "./Vector2.hpp"

namespace raylib {
/**
 * Window and Graphics Device Functions.
 */
class Window {
 public:
    /**
     * Build a Window object, but defer the initialization. Ensure you call Init() manually.
     *
     * @see Init()
     */
    Window() {
        // Nothing.
    }

    /**
     * Initialize window and OpenGL context.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The desired title of the window.
     * @param flags The ConfigFlags to set prior to initializing the window. See SetConfigFlags for more details.
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException Thrown if the window failed to initiate.
     */
    Window(int width, int height, const std::string& title = "raylib", unsigned int flags = 0) {
        Init(width, height, title, flags);
    }

    /**
     * Close window and unload OpenGL context
     */
    ~Window() {
        Close();
    }

    /**
     * Initializes the window.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The desired title of the window.
     * @param flags The ConfigFlags to set prior to initializing the window. See SetConfigFlags for more details.
     *
     * @see ::SetConfigFlags()
     * @see ConfigFlags
     *
     * @throws raylib::RaylibException Thrown if the window failed to initiate.
     */
    inline void Init(int width = 800, int height = 450, const std::string& title = "raylib", unsigned int flags = 0) {
        if (flags != 0) {
            ::SetConfigFlags(flags);
        }
        ::InitWindow(width, height, title.c_str());
        if (!::IsWindowReady()) {
            throw RaylibException("Failed to create Window");
        }
    }

    /**
     * Check if KEY_ESCAPE pressed or Close icon pressed
     */
    inline auto ShouldClose() const -> bool
    {
        return ::WindowShouldClose();
    }

    /**
     * Close window and unload OpenGL context
     */
    inline void Close() {
        if (::IsWindowReady()) {
            ::CloseWindow();
        }
    }

    /**
     * Check if cursor is on the current screen
     */
    inline auto IsCursorOnScreen() const -> bool
    {
        return ::IsCursorOnScreen();
    }

    /**
     * Check if window is currently fullscreen
     */
    inline auto IsFullscreen() const -> bool
    {
        return ::IsWindowFullscreen();
    }

    /**
     * Check if window is currently hidden
     */
    inline auto IsHidden() const -> bool
    {
        return ::IsWindowHidden();
    }

    /**
     * Check if window is currently minimized
     */
    inline auto IsMinimized() const -> bool
    {
        return ::IsWindowMinimized();
    }

    /**
     * Check if window is currently minimized
     */
    inline auto IsMaximized() const -> bool
    {
        return ::IsWindowMaximized();
    }

    /**
     * Check if window is currently focused
     */
    inline auto IsFocused() const -> bool
    {
        return ::IsWindowFocused();
    }

    /**
     * Check if window has been resized last frame
     */
    inline auto IsResized() const -> bool
    {
        return ::IsWindowResized();
    }

    /**
     * Check if one specific window flag is enabled
     */
    inline auto IsState(unsigned int flag) const -> bool
    {
        return ::IsWindowState(flag);
    }

    /**
     * Set window configuration state using flags
     */
    inline auto SetState(unsigned int flag) -> Window&
    {
        ::SetWindowState(flag);
        return *this;
    }

    /**
     * Clear window configuration state flags
     */
    inline auto ClearState(unsigned int flag) -> Window&
    {
        ::ClearWindowState(flag);
        return *this;
    }

    /**
     * Clear window with given color.
     */
    inline auto ClearBackground(const ::Color& color = BLACK) -> Window&
    {
        ::ClearBackground(color);
        return *this;
    }

    /**
     * Toggle window state: fullscreen/windowed
     */
    inline auto ToggleFullscreen() -> Window&
    {
        ::ToggleFullscreen();
        return *this;
    }

    /**
     * Set whether or not the application should be fullscreen.
     */
    inline auto SetFullscreen(bool fullscreen) -> Window&
    {
        if (fullscreen) {
            if (!IsFullscreen()) {
                ToggleFullscreen();
            }
        } else {
            if (IsFullscreen()) {
                ToggleFullscreen();
            }
        }

        return *this;
    }

    /**
     * Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
     */
    inline auto Maximize() -> Window&
    {
        ::MaximizeWindow();
        return *this;
    }

    /**
     * Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
     */
    inline auto Minimize() -> Window&
    {
        ::MinimizeWindow();
        return *this;
    }

    /**
     * Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
     */
    inline auto Restore() -> Window&
    {
        ::RestoreWindow();
        return *this;
    }

    /**
     * Set icon for window
     */
    inline auto SetIcon(const ::Image& image) -> Window&
    {
        ::SetWindowIcon(image);
        return *this;
    }

    /**
     * Set title for window
     */
    inline auto SetTitle(const std::string& title) -> Window&
    {
        ::SetWindowTitle(title.c_str());
        return *this;
    }

    /**
     * Set window position on screen
     */
    inline auto SetPosition(int x, int y) -> Window&
    {
        ::SetWindowPosition(x, y);
        return *this;
    }

    /**
     * Set window position on screen
     */
    inline auto SetPosition(const ::Vector2& position) -> Window&
    {
        return SetPosition(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    /**
     * Set monitor for the current window
     */
    inline auto SetMonitor(int monitor) -> Window&
    {
        ::SetWindowMonitor(monitor);
        return *this;
    }

    /**
     * Set window minimum dimensions
     */
    inline auto SetMinSize(int width, int height) -> Window&
    {
        ::SetWindowMinSize(width, height);
        return *this;
    }

    /**
     * Set window minimum dimensions
     */
    inline auto SetMinSize(const ::Vector2& size) -> Window&
    {
        ::SetWindowMinSize(static_cast<int>(size.x), static_cast<int>(size.y));
        return *this;
    }

    /**
     * Set window dimensions
     */
    inline auto SetSize(int width, int height) -> Window&
    {
        ::SetWindowSize(width, height);
        return *this;
    }

    /**
     * Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
     */
    inline auto SetOpacity(float opacity) -> Window&
    {
        ::SetWindowOpacity(opacity);
        return *this;
    }

    /**
     * Set window dimensions
     */
    inline auto SetSize(const ::Vector2& size) -> Window&
    {
        return SetSize(static_cast<int>(size.x), static_cast<int>(size.y));
    }

    /**
     * Get the screen's width and height.
     */
    inline auto GetSize() const -> Vector2
    {
        return {static_cast<float>(GetWidth()), static_cast<float>(GetHeight())};
    }

    /**
     * Get native window handle
     */
    inline auto GetHandle() const -> void*
    {
        return ::GetWindowHandle();
    }

    /**
     * Setup canvas (framebuffer) to start drawing
     */
    inline auto BeginDrawing() -> Window&
    {
        ::BeginDrawing();
        return *this;
    }

    /**
     * End canvas drawing and swap buffers (double buffering)
     */
    inline auto EndDrawing() -> Window&
    {
        ::EndDrawing();
        return *this;
    }

    /**
     * Get current screen width
     */
    inline auto GetWidth() const -> int
    {
        return ::GetScreenWidth();
    }

    /**
     * Get current screen height
     */
    inline auto GetHeight() const -> int
    {
        return ::GetScreenHeight();
    }

    /**
     * Get current render width (it considers HiDPI)
     */
    inline auto GetRenderWidth() const -> int
    {
        return ::GetRenderWidth();
    }

    /**
     * Get current render height (it considers HiDPI)
     */
    inline auto GetRenderHeight() const -> int
    {
        return ::GetRenderHeight();
    }

    /**
     * Get window position XY on monitor
     */
    inline auto GetPosition() const -> Vector2
    {
        return ::GetWindowPosition();
    }

    /**
     * Get window scale DPI factor
     */
    inline auto GetScaleDPI() const -> Vector2
    {
        return ::GetWindowScaleDPI();
    }

    /**
     * Set clipboard text content
     */
    inline void SetClipboardText(const std::string& text) {
        ::SetClipboardText(text.c_str());
    }

    /**
     * Get clipboard text content
     */
    inline auto GetClipboardText() -> const std::string
    {
        return ::GetClipboardText();
    }

    /**
     * Set target FPS (maximum)
     */
    inline auto SetTargetFPS(int fps) -> Window&
    {
        ::SetTargetFPS(fps);
        return *this;
    }

    /**
     * Returns current FPS
     */
    inline auto GetFPS() const -> int
    {
        return ::GetFPS();
    }

    /**
     * Draw current FPS
     */
    inline void DrawFPS(int posX = 10, int posY = 10) const {
        ::DrawFPS(posX, posY);
    }

    /**
     * Returns time in seconds for last frame drawn
     */
    inline auto GetFrameTime() const -> float
    {
        return ::GetFrameTime();
    }

    /**
     * Returns elapsed time in seconds since InitWindow()
     */
    inline auto GetTime() const -> double
    {
        return ::GetTime();
    }

    /**
     * Check if window has been initialized successfully
     */
    inline static auto IsReady() -> bool
    {
        return ::IsWindowReady();
    }

    /**
     * Sets the configuration flags for raylib.
     *
     * @param flags The ConfigFlags to apply to the configuration.
     *
     * @see ::SetConfigFlags
     */
    inline void SetConfigFlags(unsigned int flags) {
        ::SetConfigFlags(flags);
    }
};
}  // namespace raylib

using RWindow = raylib::Window;

#endif  // RAYLIB_CPP_INCLUDE_WINDOW_HPP_
