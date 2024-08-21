/**
 * C++ wrapper functions for raylib.
 */
#ifndef RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_
#define RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_

#include <string>
#include <vector>

#include "./raylib.hpp"

/**
 * Allow changing the declare type for all raylib-cpp global functions. Defaults to static.
 */
#ifndef RLCPPAPI
#define RLCPPAPI static
#endif

namespace raylib {

/**
 * Initialize window and OpenGL context
 */
RLCPPAPI inline void InitWindow(int width, int height, const std::string& title = "raylib") {
    ::InitWindow(width, height, title.c_str());
}

/**
 * Set title for window
 */
RLCPPAPI inline void SetWindowTitle(const std::string& title) {
    ::SetWindowTitle(title.c_str());
}

/**
 * Get the human-readable, UTF-8 encoded name of the primary monitor
 */
RLCPPAPI inline auto GetMonitorName(int monitor = 0) -> std::string
{
    return ::GetMonitorName(monitor);
}

/**
 * Set clipboard text content
 */
RLCPPAPI inline void SetClipboardText(const std::string& text) {
    ::SetClipboardText(text.c_str());
}

/**
 * Get clipboard text content
 */
RLCPPAPI inline auto GetClipboardText() -> std::string
{
    return ::GetClipboardText();
}

/**
 * Takes a screenshot of current screen (saved a .png)
 */
RLCPPAPI inline void TakeScreenshot(const std::string& fileName) {
    ::TakeScreenshot(fileName.c_str());
}

/**
 * Get gamepad internal name id
 */
RLCPPAPI inline auto GetGamepadName(int gamepad) -> std::string
{
    return ::GetGamepadName(gamepad);
}

/**
 * Load text data from file (read)
 */
RLCPPAPI auto LoadFileText(const std::string& fileName) -> std::string
{
    char* text = ::LoadFileText(fileName.c_str());
    std::string output(text);
    ::UnloadFileText(text);
    return output;
}

/**
 * Save text data to file (write)
 */
RLCPPAPI inline auto SaveFileText(const std::string& fileName, const std::string& text) -> bool
{
    return ::SaveFileText(fileName.c_str(), const_cast<char*>(text.c_str()));
}

/**
 * Check if file exists
 */
RLCPPAPI inline auto FileExists(const std::string& fileName) -> bool
{
    return ::FileExists(fileName.c_str());
}

/**
 * Check if directory path exists
 */
RLCPPAPI inline auto DirectoryExists(const std::string& dirPath) -> bool
{
    return ::DirectoryExists(dirPath.c_str());
}

/**
 * Check file extension (including point: .png, .wav)
 */
RLCPPAPI inline auto IsFileExtension(const std::string& fileName, const std::string& ext) -> bool
{
    return ::IsFileExtension(fileName.c_str(), ext.c_str());
}

/**
 * Get pointer to extension for a filename string (including point: ".png")
 */
RLCPPAPI inline auto GetFileExtension(const std::string& fileName) -> std::string
{
    return ::GetFileExtension(fileName.c_str());
}

/**
 * Get pointer to filename for a path string
 */
RLCPPAPI inline auto GetFileName(const std::string& filePath) -> std::string
{
    return ::GetFileName(filePath.c_str());
}

/**
 * Get filename string without extension
 */
RLCPPAPI inline auto GetFileNameWithoutExt(const std::string& filePath) -> std::string
{
    return ::GetFileNameWithoutExt(filePath.c_str());
}

/**
 * Get full path for a given fileName with path
 */
RLCPPAPI inline auto GetDirectoryPath(const std::string& filePath) -> std::string
{
    return ::GetDirectoryPath(filePath.c_str());
}

/**
 * Get previous directory path for a given path
 */
RLCPPAPI inline auto GetPrevDirectoryPath(const std::string& dirPath) -> std::string
{
    return ::GetPrevDirectoryPath(dirPath.c_str());
}

/**
 * Get current working directory
 */
RLCPPAPI inline auto GetWorkingDirectory() -> std::string
{
    return ::GetWorkingDirectory();
}

/**
 * Get filenames in a directory path
 */
RLCPPAPI auto LoadDirectoryFiles(const std::string& dirPath) -> std::vector<std::string>
{
    FilePathList files = ::LoadDirectoryFiles(dirPath.c_str());
    std::vector<std::string> output(files.paths, files.paths + files.count);
    ::UnloadDirectoryFiles(files);
    return output;
}

/**
 * Change working directory, return true on success
 */
RLCPPAPI inline auto ChangeDirectory(const std::string& dir) -> bool
{
    return ::ChangeDirectory(dir.c_str());
}

/**
 * Get dropped files names
 */
RLCPPAPI auto LoadDroppedFiles() -> std::vector<std::string>
{
    if (!::IsFileDropped()) {
        return std::vector<std::string>();
    }
    FilePathList files = ::LoadDroppedFiles();
    std::vector<std::string> output(files.paths, files.paths + files.count);
    ::UnloadDroppedFiles(files);
    return output;
}

/**
 * Get file modification time (last write time)
 */
RLCPPAPI inline long GetFileModTime(const std::string& fileName) { // NOLINT
    return ::GetFileModTime(fileName.c_str());
}

/**
 * Open URL with default system browser (if available)
 */
RLCPPAPI inline void OpenURL(const std::string& url) {
    return ::OpenURL(url.c_str());
}

/**
 * Load an image.
 */
RLCPPAPI inline auto LoadImage(const std::string& fileName) -> ::Image
{
    return ::LoadImage(fileName.c_str());
}

/**
 * Load an image from RAW file data
 */
RLCPPAPI inline auto LoadImageRaw(const std::string& fileName,
    int width, int height,
    int format, int headerSize) -> ::Image
{
    return ::LoadImageRaw(fileName.c_str(), width, height, format, headerSize);
}

/**
 * Load animated image data
 */
RLCPPAPI inline auto LoadImageAnim(const std::string& fileName, int* frames) -> ::Image
{
    return ::LoadImageAnim(fileName.c_str(), frames);
}

/**
 * Load image from memory buffer, fileType refers to extension like "png"
 */
RLCPPAPI inline auto LoadImageFromMemory(const std::string& fileType,
    const unsigned char* fileData,
    int dataSize) -> ::Image
{
    return ::LoadImageFromMemory(fileType.c_str(), fileData, dataSize);
}

/**
 * Export image data to file
 */
RLCPPAPI inline auto ExportImage(const Image& image, const std::string& fileName) -> bool
{
    return ::ExportImage(image, fileName.c_str());
}

/**
 * Export image as code file (.h) defining an array of bytes
 */
RLCPPAPI inline auto ExportImageAsCode(const Image& image, const std::string& fileName) -> bool
{
    return ::ExportImageAsCode(image, fileName.c_str());
}

/**
 * Draw text (using default font)
 */
RLCPPAPI inline void DrawText(const std::string& text, int posX, int posY, int fontSize, ::Color color) {
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

/**
 * Draw text using font and additional parameters
 */
RLCPPAPI inline void DrawTextEx(const Font& font, const std::string& text, Vector2 position,
        float fontSize, float spacing, ::Color tint) {
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
}

/**
 * Draw text using Font and pro parameters (rotation)
 */
RLCPPAPI inline void DrawTextPro(const Font& font, const std::string& text, Vector2 position,
        Vector2 origin, float rotation, float fontSize, float spacing, ::Color tint) {
    ::DrawTextPro(font, text.c_str(), position, origin, rotation, fontSize, spacing, tint);
}

/**
 * Load font from file (filename must include file extension)
 */
RLCPPAPI inline auto LoadFont(const std::string& fileName) -> ::Font
{
    return ::LoadFont(fileName.c_str());
}

/**
 * Load font from file (filename must include file extension)
 */
RLCPPAPI inline auto LoadFontEx(const std::string& fileName, int fontSize, int* fontChars, int charsCount) -> ::Font
{
    return ::LoadFontEx(fileName.c_str(), fontSize, fontChars, charsCount);
}

/**
 * Measure string width for default font
 */
RLCPPAPI inline auto MeasureText(const std::string& text, int fontSize) -> int
{
    return ::MeasureText(text.c_str(), fontSize);
}

/**
 * Check if two text string are equal
 */
RLCPPAPI inline auto TextIsEqual(const std::string& text1, const std::string& text2) -> bool
{
    return ::TextIsEqual(text1.c_str(), text2.c_str());
}

/**
 * Check if two text string are equal
 */
RLCPPAPI inline auto TextLength(const std::string& text) -> unsigned int
{
    return ::TextLength(text.c_str());
}

/**
 * Get text length, checks for '\0' ending
 */
RLAPI inline auto TextSubtext(const std::string& text, int position, int length) -> std::string
{
    return ::TextSubtext(text.c_str(), position, length);
}

/**
 * Replace text string
 */
RLAPI inline auto TextReplace(const std::string& text, const std::string& replace, const std::string& by) -> std::string
{
    const char* input = text.c_str();
    char* output = ::TextReplace(const_cast<char*>(input), replace.c_str(), by.c_str());
    if (output != NULL) {
        std::string stringOutput(output);
        free(output);
        return stringOutput;
    }
    return "";
}

/**
 * Insert text in a position
 */
RLAPI inline auto TextInsert(const std::string& text, const std::string& insert, int position) -> std::string
{
    char* output = ::TextInsert(text.c_str(), insert.c_str(), position);
    if (output != NULL) {
        std::string stringOutput(output);
        free(output);
        return stringOutput;
    }
    return "";
}

/**
 * Split text into multiple strings
 */
RLAPI inline auto TextSplit(const std::string& text, char delimiter) -> std::vector<std::string>
{
    int count;
    const char** split = ::TextSplit(text.c_str(), delimiter, &count);
    return std::vector<std::string>(split, split + count);
}

/**
 * Find first text occurrence within a string
 */
RLAPI inline auto TextFindIndex(const std::string& text, const std::string& find) -> int
{
    return ::TextFindIndex(text.c_str(), find.c_str());
}

/**
 * Get upper case version of provided string
 */
RLAPI inline auto TextToUpper(const std::string& text) -> std::string
{
    return ::TextToUpper(text.c_str());
}

/**
 * Get lower case version of provided string
 */
RLAPI inline auto TextToLower(const std::string& text) -> std::string
{
    return ::TextToLower(text.c_str());
}

/**
 * Get Pascal case notation version of provided string
 */
RLAPI inline auto TextToPascal(const std::string& text) -> std::string
{
    return ::TextToPascal(text.c_str());
}

/**
 * Get integer value from text (negative values not supported)
 */
RLAPI inline auto TextToInteger(const std::string& text) -> int
{
    return ::TextToInteger(text.c_str());
}

}  // namespace raylib

#endif  // RAYLIB_CPP_INCLUDE_FUNCTIONS_HPP_
