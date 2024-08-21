/**********************************************************************************************
*
*   raylib v4.5 - A simple and easy-to-use library to enjoy videogames programming (www.raylib.com)
*
*   FEATURES:
*       - NO external dependencies, all required libraries included with raylib
*       - Multiplatform: Windows, Linux, FreeBSD, OpenBSD, NetBSD, DragonFly,
*                        MacOS, Haiku, Android, Raspberry Pi, DRM native, HTML5.
*       - Written in plain C code (C99) in PascalCase/camelCase notation
*       - Hardware accelerated with OpenGL (1.1, 2.1, 3.3, 4.3 or ES2 - choose at compile)
*       - Unique OpenGL abstraction layer (usable as standalone module): [rlgl]
*       - Multiple Fonts formats supported (TTF, XNA fonts, AngelCode fonts)
*       - Outstanding texture formats support, including compressed formats (DXT, ETC, ASTC)
*       - Full 3d support for 3d Shapes, Models, Billboards, Heightmaps and more!
*       - Flexible Materials system, supporting classic maps and PBR maps
*       - Animated 3D models supported (skeletal bones animation) (IQM)
*       - Shaders support, including Model shaders and Postprocessing shaders
*       - Powerful math module for Vector, Matrix and Quaternion operations: [raymath]
*       - Audio loading and playing with streaming support (WAV, OGG, MP3, FLAC, XM, MOD)
*       - VR stereo rendering with configurable HMD device parameters
*       - Bindings to multiple programming languages available!
*
*   NOTES:
*       - One default Font is loaded on InitWindow()->LoadFontDefault() [core, text]
*       - One default Texture2D is loaded on rlglInit(), 1x1 white pixel R8G8B8A8 [rlgl] (OpenGL 3.3 or ES2)
*       - One default Shader is loaded on rlglInit()->rlLoadShaderDefault() [rlgl] (OpenGL 3.3 or ES2)
*       - One default RenderBatch is loaded on rlglInit()->rlLoadRenderBatch() [rlgl] (OpenGL 3.3 or ES2)
*
*   DEPENDENCIES (included):
*       [rcore] rglfw (Camilla Löwy - github.com/glfw/glfw) for window/context management and input (PLATFORM_DESKTOP)
*       [rlgl] glad (David Herberth - github.com/Dav1dde/glad) for OpenGL 3.3 extensions loading (PLATFORM_DESKTOP)
*       [raudio] miniaudio (David Reid - github.com/mackron/miniaudio) for audio device/context management
*
*   OPTIONAL DEPENDENCIES (included):
*       [rcore] msf_gif (Miles Fogle) for GIF recording
*       [rcore] sinfl (Micha Mettke) for DEFLATE decompression algorithm
*       [rcore] sdefl (Micha Mettke) for DEFLATE compression algorithm
*       [rtextures] stb_image (Sean Barret) for images loading (BMP, TGA, PNG, JPEG, HDR...)
*       [rtextures] stb_image_write (Sean Barret) for image writing (BMP, TGA, PNG, JPG)
*       [rtextures] stb_image_resize (Sean Barret) for image resizing algorithms
*       [rtext] stb_truetype (Sean Barret) for ttf fonts loading
*       [rtext] stb_rect_pack (Sean Barret) for rectangles packing
*       [rmodels] par_shapes (Philip Rideout) for parametric 3d shapes generation
*       [rmodels] tinyobj_loader_c (Syoyo Fujita) for models loading (OBJ, MTL)
*       [rmodels] cgltf (Johannes Kuhlmann) for models loading (glTF)
*       [rmodels] Model3D (bzt) for models loading (M3D, https://bztsrc.gitlab.io/model3d)
*       [raudio] dr_wav (David Reid) for WAV audio file loading
*       [raudio] dr_flac (David Reid) for FLAC audio file loading
*       [raudio] dr_mp3 (David Reid) for MP3 audio file loading
*       [raudio] stb_vorbis (Sean Barret) for OGG audio loading
*       [raudio] jar_xm (Joshua Reisenauer) for XM audio module loading
*       [raudio] jar_mod (Joshua Reisenauer) for MOD audio module loading
*
*
*   LICENSE: zlib/libpng
*
*   raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#ifndef RAYLIB_H
#define RAYLIB_H

#include <stdarg.h>     // Required for: va_list - Only used by TraceLogCallback

#define RAYLIB_VERSION_MAJOR 4
#define RAYLIB_VERSION_MINOR 5
#define RAYLIB_VERSION_PATCH 0
#define RAYLIB_VERSION  "4.5"

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #if defined(__TINYC__)
            #define __declspec(x) __attribute__((x))
        #endif
        #define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef RLAPI
    #define RLAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------
#ifndef PI
    #define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif
#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

// Allow custom memory allocators
// NOTE: Require recompiling raylib sources
#ifndef RL_MALLOC
    #define RL_MALLOC(sz)       malloc(sz)
#endif
#ifndef RL_CALLOC
    #define RL_CALLOC(n,sz)     calloc(n,sz)
#endif
#ifndef RL_REALLOC
    #define RL_REALLOC(ptr,sz)  realloc(ptr,sz)
#endif
#ifndef RL_FREE
    #define RL_FREE(ptr)        free(ptr)
#endif

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

// NOTE: We set some defines with some data types declared by raylib
// Other modules (raymath, rlgl) also require some of those types, so,
// to be able to use those other modules as standalone (not depending on raylib)
// this defines are very useful for internal check and avoid type (re)definitions
#define RL_COLOR_TYPE
#define RL_RECTANGLE_TYPE
#define RL_VECTOR2_TYPE
#define RL_VECTOR3_TYPE
#define RL_VECTOR4_TYPE
#define RL_QUATERNION_TYPE
#define RL_MATRIX_TYPE

// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define LIGHTGRAY  CLITERAL(Color){ 200, 200, 200, 255 }   // Light Gray
#define GRAY       CLITERAL(Color){ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   CLITERAL(Color){ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     CLITERAL(Color){ 253, 249, 0, 255 }     // Yellow
#define GOLD       CLITERAL(Color){ 255, 203, 0, 255 }     // Gold
#define ORANGE     CLITERAL(Color){ 255, 161, 0, 255 }     // Orange
#define PINK       CLITERAL(Color){ 255, 109, 194, 255 }   // Pink
#define RED        CLITERAL(Color){ 230, 41, 55, 255 }     // Red
#define MAROON     CLITERAL(Color){ 190, 33, 55, 255 }     // Maroon
#define GREEN      CLITERAL(Color){ 0, 228, 48, 255 }      // Green
#define LIME       CLITERAL(Color){ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  CLITERAL(Color){ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    CLITERAL(Color){ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       CLITERAL(Color){ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   CLITERAL(Color){ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     CLITERAL(Color){ 200, 122, 255, 255 }   // Purple
#define VIOLET     CLITERAL(Color){ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE CLITERAL(Color){ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      CLITERAL(Color){ 211, 176, 131, 255 }   // Beige
#define BROWN      CLITERAL(Color){ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  CLITERAL(Color){ 76, 63, 47, 255 }      // Dark Brown

#define WHITE      CLITERAL(Color){ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL(Color){ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL(Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL(Color){ 255, 0, 255, 255 }     // Magenta
#define RAYWHITE   CLITERAL(Color){ 245, 245, 245, 255 }   // My own White (raylib logo)

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Boolean type
#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
    #include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
    typedef enum bool { false = 0, true = !false } bool;
    #define RL_BOOL_TYPE
#endif

// Vector2, 2 components
typedef struct Vector2 {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2;

// Vector3, 3 components
typedef struct Vector3 {
    float x;                // Vector x component
    float y;                // Vector y component
    float z;                // Vector z component
} Vector3;

// Vector4, 4 components
typedef struct Vector4 {
    float x;                // Vector x component
    float y;                // Vector y component
    float z;                // Vector z component
    float w;                // Vector w component
} Vector4;

// Quaternion, 4 components (Vector4 alias)
typedef Vector4 Quaternion;

// Matrix, 4x4 components, column major, OpenGL style, right-handed
typedef struct Matrix {
    float m0, m4, m8, m12;  // Matrix first row (4 components)
    float m1, m5, m9, m13;  // Matrix second row (4 components)
    float m2, m6, m10, m14; // Matrix third row (4 components)
    float m3, m7, m11, m15; // Matrix fourth row (4 components)
} Matrix;

// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;

// Rectangle, 4 components
typedef struct Rectangle {
    float x;                // Rectangle top-left corner position x
    float y;                // Rectangle top-left corner position y
    float width;            // Rectangle width
    float height;           // Rectangle height
} Rectangle;

// Image, pixel data stored in CPU memory (RAM)
typedef struct Image {
    void *data;             // Image raw data
    int width;              // Image base width
    int height;             // Image base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (PixelFormat type)
} Image;

// Texture, tex data stored in GPU memory (VRAM)
typedef struct Texture {
    unsigned int id;        // OpenGL texture id
    int width;              // Texture base width
    int height;             // Texture base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (PixelFormat type)
} Texture;

// Texture2D, same as Texture
typedef Texture Texture2D;

// TextureCubemap, same as Texture
typedef Texture TextureCubemap;

// RenderTexture, fbo for texture rendering
typedef struct RenderTexture {
    unsigned int id;        // OpenGL framebuffer object id
    Texture texture;        // Color buffer attachment texture
    Texture depth;          // Depth buffer attachment texture
} RenderTexture;

// RenderTexture2D, same as RenderTexture
typedef RenderTexture RenderTexture2D;

// NPatchInfo, n-patch layout info
typedef struct NPatchInfo {
    Rectangle source;       // Texture source rectangle
    int left;               // Left border offset
    int top;                // Top border offset
    int right;              // Right border offset
    int bottom;             // Bottom border offset
    int layout;             // Layout of the n-patch: 3x3, 1x3 or 3x1
} NPatchInfo;

// GlyphInfo, font characters glyphs info
typedef struct GlyphInfo {
    int value;              // Character value (Unicode)
    int offsetX;            // Character offset X when drawing
    int offsetY;            // Character offset Y when drawing
    int advanceX;           // Character advance position X
    Image image;            // Character image data
} GlyphInfo;

// Font, font texture and GlyphInfo array data
typedef struct Font {
    int baseSize;           // Base size (default chars height)
    int glyphCount;         // Number of glyph characters
    int glyphPadding;       // Padding around the glyph characters
    Texture2D texture;      // Texture atlas containing the glyphs
    Rectangle *recs;        // Rectangles in texture for the glyphs
    GlyphInfo *glyphs;      // Glyphs info data
} Font;

// Camera, defines position/orientation in 3d space
typedef struct Camera3D {
    Vector3 position;       // Camera position
    Vector3 target;         // Camera target it looks-at
    Vector3 up;             // Camera up vector (rotation over its axis)
    float fovy;             // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
    int projection;         // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
} Camera3D;

typedef Camera3D Camera;    // Camera type fallback, defaults to Camera3D

// Camera2D, defines position/orientation in 2d space
typedef struct Camera2D {
    Vector2 offset;         // Camera offset (displacement from target)
    Vector2 target;         // Camera target (rotation and zoom origin)
    float rotation;         // Camera rotation in degrees
    float zoom;             // Camera zoom (scaling), should be 1.0f by default
} Camera2D;

// Mesh, vertex data and vao/vbo
typedef struct Mesh {
    int vertexCount;        // Number of vertices stored in arrays
    int triangleCount;      // Number of triangles stored (indexed or not)

    // Vertex attributes data
    float *vertices;        // Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
    float *texcoords;       // Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
    float *texcoords2;      // Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
    float *normals;         // Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
    float *tangents;        // Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
    unsigned char *colors;      // Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
    unsigned short *indices;    // Vertex indices (in case vertex data comes indexed)

    // Animation vertex data
    float *animVertices;    // Animated vertex positions (after bones transformations)
    float *animNormals;     // Animated normals (after bones transformations)
    unsigned char *boneIds; // Vertex bone ids, max 255 bone ids, up to 4 bones influence by vertex (skinning)
    float *boneWeights;     // Vertex bone weight, up to 4 bones influence by vertex (skinning)

    // OpenGL identifiers
    unsigned int vaoId;     // OpenGL Vertex Array Object id
    unsigned int *vboId;    // OpenGL Vertex Buffer Objects id (default vertex data)
} Mesh;

// Shader
typedef struct Shader {
    unsigned int id;        // Shader program id
    int *locs;              // Shader locations array (RL_MAX_SHADER_LOCATIONS)
} Shader;

// MaterialMap
typedef struct MaterialMap {
    Texture2D texture;      // Material map texture
    Color color;            // Material map color
    float value;            // Material map value
} MaterialMap;

// Material, includes shader and maps
typedef struct Material {
    Shader shader;          // Material shader
    MaterialMap *maps;      // Material maps array (MAX_MATERIAL_MAPS)
    float params[4];        // Material generic parameters (if required)
} Material;

// Transform, vertex transformation data
typedef struct Transform {
    Vector3 translation;    // Translation
    Quaternion rotation;    // Rotation
    Vector3 scale;          // Scale
} Transform;

// Bone, skeletal animation bone
typedef struct BoneInfo {
    char name[32];          // Bone name
    int parent;             // Bone parent
} BoneInfo;

// Model, meshes, materials and animation data
typedef struct Model {
    Matrix transform;       // Local transform matrix

    int meshCount;          // Number of meshes
    int materialCount;      // Number of materials
    Mesh *meshes;           // Meshes array
    Material *materials;    // Materials array
    int *meshMaterial;      // Mesh material number

    // Animation data
    int boneCount;          // Number of bones
    BoneInfo *bones;        // Bones information (skeleton)
    Transform *bindPose;    // Bones base transformation (pose)
} Model;

// ModelAnimation
typedef struct ModelAnimation {
    int boneCount;          // Number of bones
    int frameCount;         // Number of animation frames
    BoneInfo *bones;        // Bones information (skeleton)
    Transform **framePoses; // Poses array by frame
} ModelAnimation;

// Ray, ray for raycasting
typedef struct Ray {
    Vector3 position;       // Ray position (origin)
    Vector3 direction;      // Ray direction
} Ray;

// RayCollision, ray hit information
typedef struct RayCollision {
    bool hit;               // Did the ray hit something?
    float distance;         // Distance to the nearest hit
    Vector3 point;          // Point of the nearest hit
    Vector3 normal;         // Surface normal of hit
} RayCollision;

// BoundingBox
typedef struct BoundingBox {
    Vector3 min;            // Minimum vertex box-corner
    Vector3 max;            // Maximum vertex box-corner
} BoundingBox;

// Wave, audio wave data
typedef struct Wave {
    unsigned int frameCount;    // Total number of frames (considering channels)
    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
    void *data;                 // Buffer data pointer
} Wave;

// Opaque structs declaration
// NOTE: Actual structs are defined internally in raudio module
typedef struct rAudioBuffer rAudioBuffer;
typedef struct rAudioProcessor rAudioProcessor;

// AudioStream, custom audio stream
typedef struct AudioStream {
    rAudioBuffer *buffer;       // Pointer to internal data used by the audio system
    rAudioProcessor *processor; // Pointer to internal data processor, useful for audio effects

    unsigned int sampleRate;    // Frequency (samples per second)
    unsigned int sampleSize;    // Bit depth (bits per sample): 8, 16, 32 (24 not supported)
    unsigned int channels;      // Number of channels (1-mono, 2-stereo, ...)
} AudioStream;

// Sound
typedef struct Sound {
    AudioStream stream;         // Audio stream
    unsigned int frameCount;    // Total number of frames (considering channels)
} Sound;

// Music, audio stream, anything longer than ~10 seconds should be streamed
typedef struct Music {
    AudioStream stream;         // Audio stream
    unsigned int frameCount;    // Total number of frames (considering channels)
    bool looping;               // Music looping enable

    int ctxType;                // Type of music context (audio filetype)
    void *ctxData;              // Audio context data, depends on type
} Music;

// VrDeviceInfo, Head-Mounted-Display device parameters
typedef struct VrDeviceInfo {
    int hResolution;                // Horizontal resolution in pixels
    int vResolution;                // Vertical resolution in pixels
    float hScreenSize;              // Horizontal size in meters
    float vScreenSize;              // Vertical size in meters
    float vScreenCenter;            // Screen center in meters
    float eyeToScreenDistance;      // Distance between eye and display in meters
    float lensSeparationDistance;   // Lens separation distance in meters
    float interpupillaryDistance;   // IPD (distance between pupils) in meters
    float lensDistortionValues[4];  // Lens distortion constant parameters
    float chromaAbCorrection[4];    // Chromatic aberration correction parameters
} VrDeviceInfo;

// VrStereoConfig, VR stereo rendering configuration for simulator
typedef struct VrStereoConfig {
    Matrix projection[2];           // VR projection matrices (per eye)
    Matrix viewOffset[2];           // VR view offset matrices (per eye)
    float leftLensCenter[2];        // VR left lens center
    float rightLensCenter[2];       // VR right lens center
    float leftScreenCenter[2];      // VR left screen center
    float rightScreenCenter[2];     // VR right screen center
    float scale[2];                 // VR distortion scale
    float scaleIn[2];               // VR distortion scale in
} VrStereoConfig;

// File path list
typedef struct FilePathList {
    unsigned int capacity;          // Filepaths max entries
    unsigned int count;             // Filepaths entries count
    char **paths;                   // Filepaths entries
} FilePathList;

//----------------------------------------------------------------------------------
// Enumerators Definition
//----------------------------------------------------------------------------------
// System/Window config flags
// NOTE: Every bit registers one state (use it with bit masks)
// By default all flags are set to 0
typedef enum {
    FLAG_VSYNC_HINT         = 0x00000040,   // Set to try enabling V-Sync on GPU
    FLAG_FULLSCREEN_MODE    = 0x00000002,   // Set to run program in fullscreen
    FLAG_WINDOW_RESIZABLE   = 0x00000004,   // Set to allow resizable window
    FLAG_WINDOW_UNDECORATED = 0x00000008,   // Set to disable window decoration (frame and buttons)
    FLAG_WINDOW_HIDDEN      = 0x00000080,   // Set to hide window
    FLAG_WINDOW_MINIMIZED   = 0x00000200,   // Set to minimize window (iconify)
    FLAG_WINDOW_MAXIMIZED   = 0x00000400,   // Set to maximize window (expanded to monitor)
    FLAG_WINDOW_UNFOCUSED   = 0x00000800,   // Set to window non focused
    FLAG_WINDOW_TOPMOST     = 0x00001000,   // Set to window always on top
    FLAG_WINDOW_ALWAYS_RUN  = 0x00000100,   // Set to allow windows running while minimized
    FLAG_WINDOW_TRANSPARENT = 0x00000010,   // Set to allow transparent framebuffer
    FLAG_WINDOW_HIGHDPI     = 0x00002000,   // Set to support HighDPI
    FLAG_WINDOW_MOUSE_PASSTHROUGH = 0x00004000, // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
    FLAG_MSAA_4X_HINT       = 0x00000020,   // Set to try enabling MSAA 4X
    FLAG_INTERLACED_HINT    = 0x00010000    // Set to try enabling interlaced video format (for V3D)
} ConfigFlags;

// Trace log level
// NOTE: Organized by priority level
typedef enum {
    LOG_ALL = 0,        // Display all logs
    LOG_TRACE,          // Trace logging, intended for internal use only
    LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,           // Info logging, used for program execution info
    LOG_WARNING,        // Warning logging, used on recoverable failures
    LOG_ERROR,          // Error logging, used on unrecoverable failures
    LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE            // Disable logging
} TraceLogLevel;

// Keyboard keys (US keyboard layout)
// NOTE: Use GetKeyPressed() to allow redefining
// required keys for alternative layouts
typedef enum {
    KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    // Alphanumeric keys
    KEY_APOSTROPHE      = 39,       // Key: '
    KEY_COMMA           = 44,       // Key: ,
    KEY_MINUS           = 45,       // Key: -
    KEY_PERIOD          = 46,       // Key: .
    KEY_SLASH           = 47,       // Key: /
    KEY_ZERO            = 48,       // Key: 0
    KEY_ONE             = 49,       // Key: 1
    KEY_TWO             = 50,       // Key: 2
    KEY_THREE           = 51,       // Key: 3
    KEY_FOUR            = 52,       // Key: 4
    KEY_FIVE            = 53,       // Key: 5
    KEY_SIX             = 54,       // Key: 6
    KEY_SEVEN           = 55,       // Key: 7
    KEY_EIGHT           = 56,       // Key: 8
    KEY_NINE            = 57,       // Key: 9
    KEY_SEMICOLON       = 59,       // Key: ;
    KEY_EQUAL           = 61,       // Key: =
    KEY_A               = 65,       // Key: A | a
    KEY_B               = 66,       // Key: B | b
    KEY_C               = 67,       // Key: C | c
    KEY_D               = 68,       // Key: D | d
    KEY_E               = 69,       // Key: E | e
    KEY_F               = 70,       // Key: F | f
    KEY_G               = 71,       // Key: G | g
    KEY_H               = 72,       // Key: H | h
    KEY_I               = 73,       // Key: I | i
    KEY_J               = 74,       // Key: J | j
    KEY_K               = 75,       // Key: K | k
    KEY_L               = 76,       // Key: L | l
    KEY_M               = 77,       // Key: M | m
    KEY_N               = 78,       // Key: N | n
    KEY_O               = 79,       // Key: O | o
    KEY_P               = 80,       // Key: P | p
    KEY_Q               = 81,       // Key: Q | q
    KEY_R               = 82,       // Key: R | r
    KEY_S               = 83,       // Key: S | s
    KEY_T               = 84,       // Key: T | t
    KEY_U               = 85,       // Key: U | u
    KEY_V               = 86,       // Key: V | v
    KEY_W               = 87,       // Key: W | w
    KEY_X               = 88,       // Key: X | x
    KEY_Y               = 89,       // Key: Y | y
    KEY_Z               = 90,       // Key: Z | z
    KEY_LEFT_BRACKET    = 91,       // Key: [
    KEY_BACKSLASH       = 92,       // Key: '\'
    KEY_RIGHT_BRACKET   = 93,       // Key: ]
    KEY_GRAVE           = 96,       // Key: `
    // Function keys
    KEY_SPACE           = 32,       // Key: Space
    KEY_ESCAPE          = 256,      // Key: Esc
    KEY_ENTER           = 257,      // Key: Enter
    KEY_TAB             = 258,      // Key: Tab
    KEY_BACKSPACE       = 259,      // Key: Backspace
    KEY_INSERT          = 260,      // Key: Ins
    KEY_DELETE          = 261,      // Key: Del
    KEY_RIGHT           = 262,      // Key: Cursor right
    KEY_LEFT            = 263,      // Key: Cursor left
    KEY_DOWN            = 264,      // Key: Cursor down
    KEY_UP              = 265,      // Key: Cursor up
    KEY_PAGE_UP         = 266,      // Key: Page up
    KEY_PAGE_DOWN       = 267,      // Key: Page down
    KEY_HOME            = 268,      // Key: Home
    KEY_END             = 269,      // Key: End
    KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    KEY_NUM_LOCK        = 282,      // Key: Num lock
    KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    KEY_PAUSE           = 284,      // Key: Pause
    KEY_F1              = 290,      // Key: F1
    KEY_F2              = 291,      // Key: F2
    KEY_F3              = 292,      // Key: F3
    KEY_F4              = 293,      // Key: F4
    KEY_F5              = 294,      // Key: F5
    KEY_F6              = 295,      // Key: F6
    KEY_F7              = 296,      // Key: F7
    KEY_F8              = 297,      // Key: F8
    KEY_F9              = 298,      // Key: F9
    KEY_F10             = 299,      // Key: F10
    KEY_F11             = 300,      // Key: F11
    KEY_F12             = 301,      // Key: F12
    KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    KEY_LEFT_CONTROL    = 341,      // Key: Control left
    KEY_LEFT_ALT        = 342,      // Key: Alt left
    KEY_LEFT_SUPER      = 343,      // Key: Super left
    KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    KEY_RIGHT_ALT       = 346,      // Key: Alt right
    KEY_RIGHT_SUPER     = 347,      // Key: Super right
    KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    KEY_KP_0            = 320,      // Key: Keypad 0
    KEY_KP_1            = 321,      // Key: Keypad 1
    KEY_KP_2            = 322,      // Key: Keypad 2
    KEY_KP_3            = 323,      // Key: Keypad 3
    KEY_KP_4            = 324,      // Key: Keypad 4
    KEY_KP_5            = 325,      // Key: Keypad 5
    KEY_KP_6            = 326,      // Key: Keypad 6
    KEY_KP_7            = 327,      // Key: Keypad 7
    KEY_KP_8            = 328,      // Key: Keypad 8
    KEY_KP_9            = 329,      // Key: Keypad 9
    KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    KEY_KP_ADD          = 334,      // Key: Keypad +
    KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    KEY_KP_EQUAL        = 336,      // Key: Keypad =
    // Android key buttons
    KEY_BACK            = 4,        // Key: Android back button
    KEY_MENU            = 82,       // Key: Android menu button
    KEY_VOLUME_UP       = 24,       // Key: Android volume up button
    KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
} KeyboardKey;

// Add backwards compatibility support for deprecated names
#define MOUSE_LEFT_BUTTON   MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT_BUTTON  MOUSE_BUTTON_RIGHT
#define MOUSE_MIDDLE_BUTTON MOUSE_BUTTON_MIDDLE

// Mouse buttons
typedef enum {
    MOUSE_BUTTON_LEFT    = 0,       // Mouse button left
    MOUSE_BUTTON_RIGHT   = 1,       // Mouse button right
    MOUSE_BUTTON_MIDDLE  = 2,       // Mouse button middle (pressed wheel)
    MOUSE_BUTTON_SIDE    = 3,       // Mouse button side (advanced mouse device)
    MOUSE_BUTTON_EXTRA   = 4,       // Mouse button extra (advanced mouse device)
    MOUSE_BUTTON_FORWARD = 5,       // Mouse button forward (advanced mouse device)
    MOUSE_BUTTON_BACK    = 6,       // Mouse button back (advanced mouse device)
} MouseButton;

// Mouse cursor
typedef enum {
    MOUSE_CURSOR_DEFAULT       = 0,     // Default pointer shape
    MOUSE_CURSOR_ARROW         = 1,     // Arrow shape
    MOUSE_CURSOR_IBEAM         = 2,     // Text writing cursor shape
    MOUSE_CURSOR_CROSSHAIR     = 3,     // Cross shape
    MOUSE_CURSOR_POINTING_HAND = 4,     // Pointing hand cursor
    MOUSE_CURSOR_RESIZE_EW     = 5,     // Horizontal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NS     = 6,     // Vertical resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NWSE   = 7,     // Top-left to bottom-right diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_NESW   = 8,     // The top-right to bottom-left diagonal resize/move arrow shape
    MOUSE_CURSOR_RESIZE_ALL    = 9,     // The omnidirectional resize/move cursor shape
    MOUSE_CURSOR_NOT_ALLOWED   = 10     // The operation-not-allowed shape
} MouseCursor;

// Gamepad buttons
typedef enum {
    GAMEPAD_BUTTON_UNKNOWN = 0,         // Unknown button, just for error checking
    GAMEPAD_BUTTON_LEFT_FACE_UP,        // Gamepad left DPAD up button
    GAMEPAD_BUTTON_LEFT_FACE_RIGHT,     // Gamepad left DPAD right button
    GAMEPAD_BUTTON_LEFT_FACE_DOWN,      // Gamepad left DPAD down button
    GAMEPAD_BUTTON_LEFT_FACE_LEFT,      // Gamepad left DPAD left button
    GAMEPAD_BUTTON_RIGHT_FACE_UP,       // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
    GAMEPAD_BUTTON_RIGHT_FACE_RIGHT,    // Gamepad right button right (i.e. PS3: Square, Xbox: X)
    GAMEPAD_BUTTON_RIGHT_FACE_DOWN,     // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
    GAMEPAD_BUTTON_RIGHT_FACE_LEFT,     // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
    GAMEPAD_BUTTON_LEFT_TRIGGER_1,      // Gamepad top/back trigger left (first), it could be a trailing button
    GAMEPAD_BUTTON_LEFT_TRIGGER_2,      // Gamepad top/back trigger left (second), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_1,     // Gamepad top/back trigger right (one), it could be a trailing button
    GAMEPAD_BUTTON_RIGHT_TRIGGER_2,     // Gamepad top/back trigger right (second), it could be a trailing button
    GAMEPAD_BUTTON_MIDDLE_LEFT,         // Gamepad center buttons, left one (i.e. PS3: Select)
    GAMEPAD_BUTTON_MIDDLE,              // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
    GAMEPAD_BUTTON_MIDDLE_RIGHT,        // Gamepad center buttons, right one (i.e. PS3: Start)
    GAMEPAD_BUTTON_LEFT_THUMB,          // Gamepad joystick pressed button left
    GAMEPAD_BUTTON_RIGHT_THUMB          // Gamepad joystick pressed button right
} GamepadButton;

// Gamepad axis
typedef enum {
    GAMEPAD_AXIS_LEFT_X        = 0,     // Gamepad left stick X axis
    GAMEPAD_AXIS_LEFT_Y        = 1,     // Gamepad left stick Y axis
    GAMEPAD_AXIS_RIGHT_X       = 2,     // Gamepad right stick X axis
    GAMEPAD_AXIS_RIGHT_Y       = 3,     // Gamepad right stick Y axis
    GAMEPAD_AXIS_LEFT_TRIGGER  = 4,     // Gamepad back trigger left, pressure level: [1..-1]
    GAMEPAD_AXIS_RIGHT_TRIGGER = 5      // Gamepad back trigger right, pressure level: [1..-1]
} GamepadAxis;

// Material map index
typedef enum {
    MATERIAL_MAP_ALBEDO = 0,        // Albedo material (same as: MATERIAL_MAP_DIFFUSE)
    MATERIAL_MAP_METALNESS,         // Metalness material (same as: MATERIAL_MAP_SPECULAR)
    MATERIAL_MAP_NORMAL,            // Normal material
    MATERIAL_MAP_ROUGHNESS,         // Roughness material
    MATERIAL_MAP_OCCLUSION,         // Ambient occlusion material
    MATERIAL_MAP_EMISSION,          // Emission material
    MATERIAL_MAP_HEIGHT,            // Heightmap material
    MATERIAL_MAP_CUBEMAP,           // Cubemap material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_IRRADIANCE,        // Irradiance material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_PREFILTER,         // Prefilter material (NOTE: Uses GL_TEXTURE_CUBE_MAP)
    MATERIAL_MAP_BRDF               // Brdf material
} MaterialMapIndex;

#define MATERIAL_MAP_DIFFUSE      MATERIAL_MAP_ALBEDO
#define MATERIAL_MAP_SPECULAR     MATERIAL_MAP_METALNESS

// Shader location index
typedef enum {
    SHADER_LOC_VERTEX_POSITION = 0, // Shader location: vertex attribute: position
    SHADER_LOC_VERTEX_TEXCOORD01,   // Shader location: vertex attribute: texcoord01
    SHADER_LOC_VERTEX_TEXCOORD02,   // Shader location: vertex attribute: texcoord02
    SHADER_LOC_VERTEX_NORMAL,       // Shader location: vertex attribute: normal
    SHADER_LOC_VERTEX_TANGENT,      // Shader location: vertex attribute: tangent
    SHADER_LOC_VERTEX_COLOR,        // Shader location: vertex attribute: color
    SHADER_LOC_MATRIX_MVP,          // Shader location: matrix uniform: model-view-projection
    SHADER_LOC_MATRIX_VIEW,         // Shader location: matrix uniform: view (camera transform)
    SHADER_LOC_MATRIX_PROJECTION,   // Shader location: matrix uniform: projection
    SHADER_LOC_MATRIX_MODEL,        // Shader location: matrix uniform: model (transform)
    SHADER_LOC_MATRIX_NORMAL,       // Shader location: matrix uniform: normal
    SHADER_LOC_VECTOR_VIEW,         // Shader location: vector uniform: view
    SHADER_LOC_COLOR_DIFFUSE,       // Shader location: vector uniform: diffuse color
    SHADER_LOC_COLOR_SPECULAR,      // Shader location: vector uniform: specular color
    SHADER_LOC_COLOR_AMBIENT,       // Shader location: vector uniform: ambient color
    SHADER_LOC_MAP_ALBEDO,          // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
    SHADER_LOC_MAP_METALNESS,       // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
    SHADER_LOC_MAP_NORMAL,          // Shader location: sampler2d texture: normal
    SHADER_LOC_MAP_ROUGHNESS,       // Shader location: sampler2d texture: roughness
    SHADER_LOC_MAP_OCCLUSION,       // Shader location: sampler2d texture: occlusion
    SHADER_LOC_MAP_EMISSION,        // Shader location: sampler2d texture: emission
    SHADER_LOC_MAP_HEIGHT,          // Shader location: sampler2d texture: height
    SHADER_LOC_MAP_CUBEMAP,         // Shader location: samplerCube texture: cubemap
    SHADER_LOC_MAP_IRRADIANCE,      // Shader location: samplerCube texture: irradiance
    SHADER_LOC_MAP_PREFILTER,       // Shader location: samplerCube texture: prefilter
    SHADER_LOC_MAP_BRDF             // Shader location: sampler2d texture: brdf
} ShaderLocationIndex;

#define SHADER_LOC_MAP_DIFFUSE      SHADER_LOC_MAP_ALBEDO
#define SHADER_LOC_MAP_SPECULAR     SHADER_LOC_MAP_METALNESS

// Shader uniform data type
typedef enum {
    SHADER_UNIFORM_FLOAT = 0,       // Shader uniform type: float
    SHADER_UNIFORM_VEC2,            // Shader uniform type: vec2 (2 float)
    SHADER_UNIFORM_VEC3,            // Shader uniform type: vec3 (3 float)
    SHADER_UNIFORM_VEC4,            // Shader uniform type: vec4 (4 float)
    SHADER_UNIFORM_INT,             // Shader uniform type: int
    SHADER_UNIFORM_IVEC2,           // Shader uniform type: ivec2 (2 int)
    SHADER_UNIFORM_IVEC3,           // Shader uniform type: ivec3 (3 int)
    SHADER_UNIFORM_IVEC4,           // Shader uniform type: ivec4 (4 int)
    SHADER_UNIFORM_SAMPLER2D        // Shader uniform type: sampler2d
} ShaderUniformDataType;

// Shader attribute data types
typedef enum {
    SHADER_ATTRIB_FLOAT = 0,        // Shader attribute type: float
    SHADER_ATTRIB_VEC2,             // Shader attribute type: vec2 (2 float)
    SHADER_ATTRIB_VEC3,             // Shader attribute type: vec3 (3 float)
    SHADER_ATTRIB_VEC4              // Shader attribute type: vec4 (4 float)
} ShaderAttributeDataType;

// Pixel formats
// NOTE: Support depends on OpenGL version and platform
typedef enum {
    PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
    PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
    PIXELFORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
    PIXELFORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
    PIXELFORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
    PIXELFORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
    PIXELFORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
    PIXELFORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
    PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp
} PixelFormat;

// Texture parameters: filter mode
// NOTE 1: Filtering considers mipmaps if available in the texture
// NOTE 2: Filter is accordingly set for minification and magnification
typedef enum {
    TEXTURE_FILTER_POINT = 0,               // No filter, just pixel approximation
    TEXTURE_FILTER_BILINEAR,                // Linear filtering
    TEXTURE_FILTER_TRILINEAR,               // Trilinear filtering (linear with mipmaps)
    TEXTURE_FILTER_ANISOTROPIC_4X,          // Anisotropic filtering 4x
    TEXTURE_FILTER_ANISOTROPIC_8X,          // Anisotropic filtering 8x
    TEXTURE_FILTER_ANISOTROPIC_16X,         // Anisotropic filtering 16x
} TextureFilter;

// Texture parameters: wrap mode
typedef enum {
    TEXTURE_WRAP_REPEAT = 0,                // Repeats texture in tiled mode
    TEXTURE_WRAP_CLAMP,                     // Clamps texture to edge pixel in tiled mode
    TEXTURE_WRAP_MIRROR_REPEAT,             // Mirrors and repeats the texture in tiled mode
    TEXTURE_WRAP_MIRROR_CLAMP               // Mirrors and clamps to border the texture in tiled mode
} TextureWrap;

// Cubemap layouts
typedef enum {
    CUBEMAP_LAYOUT_AUTO_DETECT = 0,         // Automatically detect layout type
    CUBEMAP_LAYOUT_LINE_VERTICAL,           // Layout is defined by a vertical line with faces
    CUBEMAP_LAYOUT_LINE_HORIZONTAL,         // Layout is defined by a horizontal line with faces
    CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR,     // Layout is defined by a 3x4 cross with cubemap faces
    CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE,     // Layout is defined by a 4x3 cross with cubemap faces
    CUBEMAP_LAYOUT_PANORAMA                 // Layout is defined by a panorama image (equirrectangular map)
} CubemapLayout;

// Font type, defines generation method
typedef enum {
    FONT_DEFAULT = 0,               // Default font generation, anti-aliased
    FONT_BITMAP,                    // Bitmap font generation, no anti-aliasing
    FONT_SDF                        // SDF font generation, requires external shader
} FontType;

// Color blending modes (pre-defined)
typedef enum {
    BLEND_ALPHA = 0,                // Blend textures considering alpha (default)
    BLEND_ADDITIVE,                 // Blend textures adding colors
    BLEND_MULTIPLIED,               // Blend textures multiplying colors
    BLEND_ADD_COLORS,               // Blend textures adding colors (alternative)
    BLEND_SUBTRACT_COLORS,          // Blend textures subtracting colors (alternative)
    BLEND_ALPHA_PREMULTIPLY,        // Blend premultiplied textures considering alpha
    BLEND_CUSTOM,                   // Blend textures using custom src/dst factors (use rlSetBlendFactors())
    BLEND_CUSTOM_SEPARATE           // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
} BlendMode;

// Gesture
// NOTE: Provided as bit-wise flags to enable only desired gestures
typedef enum {
    GESTURE_NONE        = 0,        // No gesture
    GESTURE_TAP         = 1,        // Tap gesture
    GESTURE_DOUBLETAP   = 2,        // Double tap gesture
    GESTURE_HOLD        = 4,        // Hold gesture
    GESTURE_DRAG        = 8,        // Drag gesture
    GESTURE_SWIPE_RIGHT = 16,       // Swipe right gesture
    GESTURE_SWIPE_LEFT  = 32,       // Swipe left gesture
    GESTURE_SWIPE_UP    = 64,       // Swipe up gesture
    GESTURE_SWIPE_DOWN  = 128,      // Swipe down gesture
    GESTURE_PINCH_IN    = 256,      // Pinch in gesture
    GESTURE_PINCH_OUT   = 512       // Pinch out gesture
} Gesture;

// Camera system modes
typedef enum {
    CAMERA_CUSTOM = 0,              // Custom camera
    CAMERA_FREE,                    // Free camera
    CAMERA_ORBITAL,                 // Orbital camera
    CAMERA_FIRST_PERSON,            // First person camera
    CAMERA_THIRD_PERSON             // Third person camera
} CameraMode;

// Camera projection
typedef enum {
    CAMERA_PERSPECTIVE = 0,         // Perspective projection
    CAMERA_ORTHOGRAPHIC             // Orthographic projection
} CameraProjection;

// N-patch layout
typedef enum {
    NPATCH_NINE_PATCH = 0,          // Npatch layout: 3x3 tiles
    NPATCH_THREE_PATCH_VERTICAL,    // Npatch layout: 1x3 tiles
    NPATCH_THREE_PATCH_HORIZONTAL   // Npatch layout: 3x1 tiles
} NPatchLayout;

// Callbacks to hook some internal functions
// WARNING: These callbacks are intended for advance users
typedef void (*TraceLogCallback)(int logLevel, const char *text, va_list args);  // Logging: Redirect trace log messages
typedef unsigned char *(*LoadFileDataCallback)(const char *fileName, unsigned int *bytesRead);      // FileIO: Load binary data
typedef bool (*SaveFileDataCallback)(const char *fileName, void *data, unsigned int bytesToWrite);  // FileIO: Save binary data
typedef char *(*LoadFileTextCallback)(const char *fileName);            // FileIO: Load text data
typedef bool (*SaveFileTextCallback)(const char *fileName, char *text); // FileIO: Save text data

//------------------------------------------------------------------------------------
// Global Variables Definition
//------------------------------------------------------------------------------------
// It's lonely here...

//------------------------------------------------------------------------------------
// Window and Graphics Device Functions (Module: core)
//------------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

// Window-related functions
RLAPI void InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
RLAPI auto WindowShouldClose(void) -> bool; // Check if KEY_ESCAPE pressed or Close icon pressed
RLAPI void CloseWindow(void);                                     // Close window and unload OpenGL context
RLAPI auto IsWindowReady(void) -> bool; // Check if window has been initialized successfully
RLAPI auto IsWindowFullscreen(void) -> bool; // Check if window is currently fullscreen
RLAPI auto IsWindowHidden(void) -> bool; // Check if window is currently hidden (only PLATFORM_DESKTOP)
RLAPI auto IsWindowMinimized(void) -> bool; // Check if window is currently minimized (only PLATFORM_DESKTOP)
RLAPI auto IsWindowMaximized(void) -> bool; // Check if window is currently maximized (only PLATFORM_DESKTOP)
RLAPI auto IsWindowFocused(void) -> bool; // Check if window is currently focused (only PLATFORM_DESKTOP)
RLAPI auto IsWindowResized(void) -> bool; // Check if window has been resized last frame
RLAPI auto IsWindowState(unsigned int flag) -> bool; // Check if one specific window flag is enabled
RLAPI void SetWindowState(unsigned int flags);                    // Set window configuration state using flags (only PLATFORM_DESKTOP)
RLAPI void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
RLAPI void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
RLAPI void MaximizeWindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
RLAPI void MinimizeWindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
RLAPI void RestoreWindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
RLAPI void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void SetWindowIcons(Image *images, int count);              // Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
RLAPI void SetWindowTitle(const char *title);                     // Set title for window (only PLATFORM_DESKTOP)
RLAPI void SetWindowPosition(int x, int y);                       // Set window position on screen (only PLATFORM_DESKTOP)
RLAPI void SetWindowMonitor(int monitor);                         // Set monitor for the current window (fullscreen mode)
RLAPI void SetWindowMinSize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
RLAPI void SetWindowSize(int width, int height);                  // Set window dimensions
RLAPI void SetWindowOpacity(float opacity);                       // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
RLAPI auto GetWindowHandle(void) -> void*; // Get native window handle
RLAPI auto GetScreenWidth(void) -> int; // Get current screen width
RLAPI auto GetScreenHeight(void) -> int; // Get current screen height
RLAPI auto GetRenderWidth(void) -> int; // Get current render width (it considers HiDPI)
RLAPI auto GetRenderHeight(void) -> int; // Get current render height (it considers HiDPI)
RLAPI auto GetMonitorCount(void) -> int; // Get number of connected monitors
RLAPI auto GetCurrentMonitor(void) -> int; // Get current connected monitor
RLAPI auto GetMonitorPosition(int monitor) -> Vector2; // Get specified monitor position
RLAPI auto GetMonitorWidth(int monitor) -> int; // Get specified monitor width (current video mode used by monitor)
RLAPI auto GetMonitorHeight(int monitor) -> int; // Get specified monitor height (current video mode used by monitor)
RLAPI auto GetMonitorPhysicalWidth(int monitor) -> int; // Get specified monitor physical width in millimetres
RLAPI auto GetMonitorPhysicalHeight(int monitor) -> int; // Get specified monitor physical height in millimetres
RLAPI auto GetMonitorRefreshRate(int monitor) -> int; // Get specified monitor refresh rate
RLAPI auto GetWindowPosition(void) -> Vector2; // Get window position XY on monitor
RLAPI auto GetWindowScaleDPI(void) -> Vector2; // Get window scale DPI factor
RLAPI auto GetMonitorName(int monitor) -> const char*; // Get the human-readable, UTF-8 encoded name of the primary monitor
RLAPI void SetClipboardText(const char *text);                    // Set clipboard text content
RLAPI auto GetClipboardText(void) -> const char*; // Get clipboard text content
RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling

// Custom frame control functions
// NOTE: Those functions are intended for advance users that want full control over the frame processing
// By default EndDrawing() does this job: draws everything + SwapScreenBuffer() + manage frame timing + PollInputEvents()
// To avoid that behaviour and control frame processes manually, enable in config.h: SUPPORT_CUSTOM_FRAME_CONTROL
RLAPI void SwapScreenBuffer(void);                                // Swap back buffer with front buffer (screen drawing)
RLAPI void PollInputEvents(void);                                 // Register all input events
RLAPI void WaitTime(double seconds);                              // Wait for some time (halt program execution)

// Cursor-related functions
RLAPI void ShowCursor(void);                                      // Shows cursor
RLAPI void HideCursor(void);                                      // Hides cursor
RLAPI auto IsCursorHidden(void) -> bool; // Check if cursor is not visible
RLAPI void EnableCursor(void);                                    // Enables cursor (unlock cursor)
RLAPI void DisableCursor(void);                                   // Disables cursor (lock cursor)
RLAPI auto IsCursorOnScreen(void) -> bool; // Check if cursor is on the screen

// Drawing-related functions
RLAPI void ClearBackground(Color color);                          // Set background color (framebuffer clear color)
RLAPI void BeginDrawing(void);                                    // Setup canvas (framebuffer) to start drawing
RLAPI void EndDrawing(void);                                      // End canvas drawing and swap buffers (double buffering)
RLAPI void BeginMode2D(Camera2D camera);                          // Begin 2D mode with custom camera (2D)
RLAPI void EndMode2D(void);                                       // Ends 2D mode with custom camera
RLAPI void BeginMode3D(Camera3D camera);                          // Begin 3D mode with custom camera (3D)
RLAPI void EndMode3D(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
RLAPI void BeginTextureMode(RenderTexture2D target);              // Begin drawing to render texture
RLAPI void EndTextureMode(void);                                  // Ends drawing to render texture
RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
RLAPI void EndScissorMode(void);                                  // End scissor mode
RLAPI void BeginVrStereoMode(VrStereoConfig config);              // Begin stereo rendering (requires VR simulator)
RLAPI void EndVrStereoMode(void);                                 // End stereo rendering (requires VR simulator)

// VR stereo config functions for VR simulator
RLAPI auto LoadVrStereoConfig(VrDeviceInfo device) -> VrStereoConfig; // Load VR stereo config for VR simulator device parameters
RLAPI void UnloadVrStereoConfig(VrStereoConfig config);           // Unload VR stereo config

// Shader management functions
// NOTE: Shader functionality is not available on OpenGL 1.1
RLAPI auto LoadShader(const char* vsFileName, const char* fsFileName) -> Shader; // Load shader from files and bind default locations
RLAPI auto LoadShaderFromMemory(const char* vsCode, const char* fsCode) -> Shader; // Load shader from code strings and bind default locations
RLAPI auto IsShaderReady(Shader shader) -> bool; // Check if a shader is ready
RLAPI auto GetShaderLocation(Shader shader, const char* uniformName) -> int; // Get shader uniform location
RLAPI auto GetShaderLocationAttrib(Shader shader, const char* attribName) -> int; // Get shader attribute location
RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);         // Set shader uniform value (matrix 4x4)
RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value for texture (sampler2d)
RLAPI void UnloadShader(Shader shader);                                    // Unload shader from GPU memory (VRAM)

// Screen-space-related functions
RLAPI auto GetMouseRay(Vector2 mousePosition, Camera camera) -> Ray; // Get a ray trace from mouse position
RLAPI auto GetCameraMatrix(Camera camera) -> Matrix; // Get camera transform matrix (view matrix)
RLAPI auto GetCameraMatrix2D(Camera2D camera) -> Matrix; // Get camera 2d transform matrix
RLAPI auto GetWorldToScreen(Vector3 position, Camera camera) -> Vector2; // Get the screen space position for a 3d world space position
RLAPI auto GetScreenToWorld2D(Vector2 position, Camera2D camera) -> Vector2; // Get the world space position for a 2d camera screen space position
RLAPI auto GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height) -> Vector2; // Get size position for a 3d world space position
RLAPI auto GetWorldToScreen2D(Vector2 position, Camera2D camera) -> Vector2; // Get the screen space position for a 2d camera world space position

// Timing-related functions
RLAPI void SetTargetFPS(int fps);                                 // Set target FPS (maximum)
RLAPI auto GetFPS(void) -> int; // Get current FPS
RLAPI auto GetFrameTime(void) -> float; // Get time in seconds for last frame drawn (delta time)
RLAPI auto GetTime(void) -> double; // Get elapsed time in seconds since InitWindow()

// Misc. functions
RLAPI auto GetRandomValue(int min, int max) -> int; // Get a random value between min and max (both included)
RLAPI void SetRandomSeed(unsigned int seed);                      // Set the seed for the random number generator
RLAPI void TakeScreenshot(const char *fileName);                  // Takes a screenshot of current screen (filename extension defines format)
RLAPI void SetConfigFlags(unsigned int flags);                    // Setup init configuration flags (view FLAGS)

RLAPI void TraceLog(int logLevel, const char *text, ...);         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
RLAPI void SetTraceLogLevel(int logLevel);                        // Set the current threshold (minimum) log level
RLAPI auto MemAlloc(unsigned int size) -> void*; // Internal memory allocator
RLAPI auto MemRealloc(void* ptr, unsigned int size) -> void*; // Internal memory reallocator
RLAPI void MemFree(void *ptr);                                    // Internal memory free

RLAPI void OpenURL(const char *url);                              // Open URL with default system browser (if available)

// Set custom callbacks
// WARNING: Callbacks setup is intended for advance users
RLAPI void SetTraceLogCallback(TraceLogCallback callback);         // Set custom trace log
RLAPI void SetLoadFileDataCallback(LoadFileDataCallback callback); // Set custom file binary data loader
RLAPI void SetSaveFileDataCallback(SaveFileDataCallback callback); // Set custom file binary data saver
RLAPI void SetLoadFileTextCallback(LoadFileTextCallback callback); // Set custom file text data loader
RLAPI void SetSaveFileTextCallback(SaveFileTextCallback callback); // Set custom file text data saver

// Files management functions
RLAPI auto LoadFileData(const char* fileName, unsigned int* bytesRead) -> unsigned char*; // Load file data as byte array (read)
RLAPI void UnloadFileData(unsigned char *data);                   // Unload file data allocated by LoadFileData()
RLAPI auto SaveFileData(const char* fileName, void* data, unsigned int bytesToWrite) -> bool; // Save data to file from byte array (write), returns true on success
RLAPI auto ExportDataAsCode(const unsigned char* data, unsigned int size, const char* fileName) -> bool; // Export data to code (.h), returns true on success
RLAPI auto LoadFileText(const char* fileName) -> char*; // Load text data from file (read), returns a '\0' terminated string
RLAPI void UnloadFileText(char *text);                            // Unload file text data allocated by LoadFileText()
RLAPI auto SaveFileText(const char* fileName, char* text) -> bool; // Save text data to file (write), string must be '\0' terminated, returns true on success
RLAPI auto FileExists(const char* fileName) -> bool; // Check if file exists
RLAPI auto DirectoryExists(const char* dirPath) -> bool; // Check if a directory path exists
RLAPI auto IsFileExtension(const char* fileName, const char* ext) -> bool; // Check file extension (including point: .png, .wav)
RLAPI auto GetFileLength(const char* fileName) -> int; // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
RLAPI auto GetFileExtension(const char* fileName) -> const char*; // Get pointer to extension for a filename string (includes dot: '.png')
RLAPI auto GetFileName(const char* filePath) -> const char*; // Get pointer to filename for a path string
RLAPI auto GetFileNameWithoutExt(const char* filePath) -> const char*; // Get filename string without extension (uses static string)
RLAPI auto GetDirectoryPath(const char* filePath) -> const char*; // Get full path for a given fileName with path (uses static string)
RLAPI auto GetPrevDirectoryPath(const char* dirPath) -> const char*; // Get previous directory path for a given path (uses static string)
RLAPI auto GetWorkingDirectory(void) -> const char*; // Get current working directory (uses static string)
RLAPI auto GetApplicationDirectory(void) -> const char*; // Get the directory if the running application (uses static string)
RLAPI auto ChangeDirectory(const char* dir) -> bool; // Change working directory, return true on success
RLAPI auto IsPathFile(const char* path) -> bool; // Check if a given path is a file or a directory
RLAPI auto LoadDirectoryFiles(const char* dirPath) -> FilePathList; // Load directory filepaths
RLAPI auto LoadDirectoryFilesEx(const char* basePath, const char* filter, bool scanSubdirs) -> FilePathList; // Load directory filepaths with extension filtering and recursive directory scan
RLAPI void UnloadDirectoryFiles(FilePathList files);              // Unload filepaths
RLAPI auto IsFileDropped(void) -> bool; // Check if a file has been dropped into window
RLAPI auto LoadDroppedFiles(void) -> FilePathList; // Load dropped filepaths
RLAPI void UnloadDroppedFiles(FilePathList files);                // Unload dropped filepaths
RLAPI auto GetFileModTime(const char* fileName) -> long; // Get file modification time (last write time)

// Compression/Encoding functionality
RLAPI auto CompressData(const unsigned char* data, int dataSize, int* compDataSize) -> unsigned char*; // Compress data (DEFLATE algorithm), memory must be MemFree()
RLAPI auto DecompressData(const unsigned char* compData, int compDataSize, int* dataSize) -> unsigned char*; // Decompress data (DEFLATE algorithm), memory must be MemFree()
RLAPI auto EncodeDataBase64(const unsigned char* data, int dataSize, int* outputSize) -> char*; // Encode data to Base64 string, memory must be MemFree()
RLAPI auto DecodeDataBase64(const unsigned char* data, int* outputSize) -> unsigned char*; // Decode Base64 string data, memory must be MemFree()

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard
RLAPI auto IsKeyPressed(int key) -> bool; // Check if a key has been pressed once
RLAPI auto IsKeyDown(int key) -> bool; // Check if a key is being pressed
RLAPI auto IsKeyReleased(int key) -> bool; // Check if a key has been released once
RLAPI auto IsKeyUp(int key) -> bool; // Check if a key is NOT being pressed
RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
RLAPI auto GetKeyPressed(void) -> int; // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
RLAPI auto GetCharPressed(void) -> int; // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty

// Input-related functions: gamepads
RLAPI auto IsGamepadAvailable(int gamepad) -> bool; // Check if a gamepad is available
RLAPI auto GetGamepadName(int gamepad) -> const char*; // Get gamepad internal name id
RLAPI auto IsGamepadButtonPressed(int gamepad, int button) -> bool; // Check if a gamepad button has been pressed once
RLAPI auto IsGamepadButtonDown(int gamepad, int button) -> bool; // Check if a gamepad button is being pressed
RLAPI auto IsGamepadButtonReleased(int gamepad, int button) -> bool; // Check if a gamepad button has been released once
RLAPI auto IsGamepadButtonUp(int gamepad, int button) -> bool; // Check if a gamepad button is NOT being pressed
RLAPI auto GetGamepadButtonPressed(void) -> int; // Get the last gamepad button pressed
RLAPI auto GetGamepadAxisCount(int gamepad) -> int; // Get gamepad axis count for a gamepad
RLAPI auto GetGamepadAxisMovement(int gamepad, int axis) -> float; // Get axis movement value for a gamepad axis
RLAPI auto SetGamepadMappings(const char* mappings) -> int; // Set internal gamepad mappings (SDL_GameControllerDB)

// Input-related functions: mouse
RLAPI auto IsMouseButtonPressed(int button) -> bool; // Check if a mouse button has been pressed once
RLAPI auto IsMouseButtonDown(int button) -> bool; // Check if a mouse button is being pressed
RLAPI auto IsMouseButtonReleased(int button) -> bool; // Check if a mouse button has been released once
RLAPI auto IsMouseButtonUp(int button) -> bool; // Check if a mouse button is NOT being pressed
RLAPI auto GetMouseX(void) -> int; // Get mouse position X
RLAPI auto GetMouseY(void) -> int; // Get mouse position Y
RLAPI auto GetMousePosition(void) -> Vector2; // Get mouse position XY
RLAPI auto GetMouseDelta(void) -> Vector2; // Get mouse delta between frames
RLAPI void SetMousePosition(int x, int y);                    // Set mouse position XY
RLAPI void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
RLAPI void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
RLAPI auto GetMouseWheelMove(void) -> float; // Get mouse wheel movement for X or Y, whichever is larger
RLAPI auto GetMouseWheelMoveV(void) -> Vector2; // Get mouse wheel movement for both X and Y
RLAPI void SetMouseCursor(int cursor);                        // Set mouse cursor

// Input-related functions: touch
RLAPI auto GetTouchX(void) -> int; // Get touch position X for touch point 0 (relative to screen size)
RLAPI auto GetTouchY(void) -> int; // Get touch position Y for touch point 0 (relative to screen size)
RLAPI auto GetTouchPosition(int index) -> Vector2; // Get touch position XY for a touch point index (relative to screen size)
RLAPI auto GetTouchPointId(int index) -> int; // Get touch point identifier for given index
RLAPI auto GetTouchPointCount(void) -> int; // Get number of touch points

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: rgestures)
//------------------------------------------------------------------------------------
RLAPI void SetGesturesEnabled(unsigned int flags);      // Enable a set of gestures using flags
RLAPI auto IsGestureDetected(int gesture) -> bool; // Check if a gesture have been detected
RLAPI auto GetGestureDetected(void) -> int; // Get latest detected gesture
RLAPI auto GetGestureHoldDuration(void) -> float; // Get gesture hold time in milliseconds
RLAPI auto GetGestureDragVector(void) -> Vector2; // Get gesture drag vector
RLAPI auto GetGestureDragAngle(void) -> float; // Get gesture drag angle
RLAPI auto GetGesturePinchVector(void) -> Vector2; // Get gesture pinch delta
RLAPI auto GetGesturePinchAngle(void) -> float; // Get gesture pinch angle

//------------------------------------------------------------------------------------
// Camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
RLAPI void UpdateCamera(Camera *camera, int mode);      // Update camera position for selected mode
RLAPI void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation

//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
// Set texture and rectangle to be used on shapes drawing
// NOTE: It can be useful when using basic shapes and one single font,
// defining a font char white rectangle would allow drawing everything in a single draw call
RLAPI void SetShapesTexture(Texture2D texture, Rectangle source);       // Set texture and rectangle to be used on shapes drawing

// Basic shapes drawing functions
RLAPI void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel
RLAPI void DrawPixelV(Vector2 position, Color color);                                                    // Draw a pixel (Vector version)
RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                // Draw a line
RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     // Draw a line (Vector version)
RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                       // Draw a line defining thickness
RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   // Draw a line using cubic-bezier curves in-out
RLAPI void DrawLineBezierQuad(Vector2 startPos, Vector2 endPos, Vector2 controlPos, float thick, Color color); // Draw line using quadratic bezier curves with a control point
RLAPI void DrawLineBezierCubic(Vector2 startPos, Vector2 endPos, Vector2 startControlPos, Vector2 endControlPos, float thick, Color color); // Draw line using cubic bezier curves with 2 control points
RLAPI void DrawLineStrip(Vector2 *points, int pointCount, Color color);                                  // Draw lines sequence
RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
RLAPI void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color);      // Draw a piece of a circle
RLAPI void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline
RLAPI void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);       // Draw a gradient-filled circle
RLAPI void DrawCircleV(Vector2 center, float radius, Color color);                                       // Draw a color-filled circle (Vector version)
RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse
RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);        // Draw ellipse outline
RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring
RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color);    // Draw ring outline
RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 // Draw a color-filled rectangle with pro parameters
RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a vertical-gradient-filled rectangle
RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);// Draw a horizontal-gradient-filled rectangle
RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);       // Draw a gradient-filled rectangle with custom vertex colors
RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
RLAPI void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle with rounded edges outline
RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)
RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline (vertex in counter-clockwise order!)
RLAPI void DrawTriangleFan(Vector2 *points, int pointCount, Color color);                                // Draw a triangle fan defined by points (first vertex is the center)
RLAPI void DrawTriangleStrip(Vector2 *points, int pointCount, Color color);                              // Draw a triangle strip defined by points
RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a regular polygon (Vector version)
RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);          // Draw a polygon outline of n sides
RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color); // Draw a polygon outline of n sides with extended parameters

// Basic shapes collision detection functions
RLAPI auto CheckCollisionRecs(Rectangle rec1, Rectangle rec2) -> bool; // Check collision between two rectangles
RLAPI auto CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2) -> bool; // Check collision between two circles
RLAPI auto CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec) -> bool; // Check collision between circle and rectangle
RLAPI auto CheckCollisionPointRec(Vector2 point, Rectangle rec) -> bool; // Check if point is inside rectangle
RLAPI auto CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius) -> bool; // Check if point is inside circle
RLAPI auto CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3) -> bool; // Check if point is inside a triangle
RLAPI auto CheckCollisionPointPoly(Vector2 point, Vector2* points, int pointCount) -> bool; // Check if point is within a polygon described by array of vertices
RLAPI auto CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2* collisionPoint) -> bool; // Check the collision between two lines defined by two points each, returns collision point by reference
RLAPI auto CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold) -> bool; // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
RLAPI auto GetCollisionRec(Rectangle rec1, Rectangle rec2) -> Rectangle; // Get collision rectangle for two rectangles collision

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image loading functions
// NOTE: These functions do not require GPU access
RLAPI auto LoadImage(const char* fileName) -> Image; // Load image from file into CPU memory (RAM)
RLAPI auto LoadImageRaw(const char* fileName, int width, int height, int format, int headerSize) -> Image; // Load image from RAW file data
RLAPI auto LoadImageAnim(const char* fileName, int* frames) -> Image; // Load image sequence from file (frames appended to image.data)
RLAPI auto LoadImageFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) -> Image; // Load image from memory buffer, fileType refers to extension: i.e. '.png'
RLAPI auto LoadImageFromTexture(Texture2D texture) -> Image; // Load image from GPU texture data
RLAPI auto LoadImageFromScreen(void) -> Image; // Load image from screen buffer and (screenshot)
RLAPI auto IsImageReady(Image image) -> bool; // Check if an image is ready
RLAPI void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
RLAPI auto ExportImage(Image image, const char* fileName) -> bool; // Export image data to file, returns true on success
RLAPI auto ExportImageAsCode(Image image, const char* fileName) -> bool; // Export image as code file defining an array of bytes, returns true on success

// Image generation functions
RLAPI auto GenImageColor(int width, int height, Color color) -> Image; // Generate image: plain color
RLAPI auto GenImageGradientV(int width, int height, Color top, Color bottom) -> Image; // Generate image: vertical gradient
RLAPI auto GenImageGradientH(int width, int height, Color left, Color right) -> Image; // Generate image: horizontal gradient
RLAPI auto GenImageGradientRadial(int width, int height, float density, Color inner, Color outer) -> Image; // Generate image: radial gradient
RLAPI auto GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2) -> Image; // Generate image: checked
RLAPI auto GenImageWhiteNoise(int width, int height, float factor) -> Image; // Generate image: white noise
RLAPI auto GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale) -> Image; // Generate image: perlin noise
RLAPI auto GenImageCellular(int width, int height, int tileSize) -> Image; // Generate image: cellular algorithm, bigger tileSize means bigger cells
RLAPI auto GenImageText(int width, int height, const char* text) -> Image; // Generate image: grayscale image from text data

// Image manipulation functions
RLAPI auto ImageCopy(Image image) -> Image; // Create an image duplicate (useful for transformations)
RLAPI auto ImageFromImage(Image image, Rectangle rec) -> Image; // Create an image from another image piece
RLAPI auto ImageText(const char* text, int fontSize, Color color) -> Image; // Create an image from text (default font)
RLAPI auto ImageTextEx(Font font, const char* text, float fontSize, float spacing, Color tint) -> Image; // Create an image from text (custom sprite font)
RLAPI void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
RLAPI void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
RLAPI void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
RLAPI void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
RLAPI void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
RLAPI void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
RLAPI void ImageBlurGaussian(Image *image, int blurSize);                                                // Apply Gaussian blur using a box blur approximation
RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
RLAPI void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);  // Resize canvas and fill with color
RLAPI void ImageMipmaps(Image *image);                                                                   // Compute all mipmap levels for a provided image
RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
RLAPI void ImageFlipVertical(Image *image);                                                              // Flip image vertically
RLAPI void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
RLAPI void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
RLAPI void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
RLAPI void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
RLAPI void ImageColorInvert(Image *image);                                                               // Modify image color: invert
RLAPI void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
RLAPI void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
RLAPI void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
RLAPI void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
RLAPI auto LoadImageColors(Image image) -> Color*; // Load color data from image as a Color array (RGBA - 32bit)
RLAPI auto LoadImagePalette(Image image, int maxPaletteSize, int* colorCount) -> Color*; // Load colors palette from image as a Color array (RGBA - 32bit)
RLAPI void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
RLAPI void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
RLAPI auto GetImageAlphaBorder(Image image, float threshold) -> Rectangle; // Get image alpha border rectangle
RLAPI auto GetImageColor(Image image, int x, int y) -> Color; // Get image pixel color at (x, y) position

// Image drawing functions
// NOTE: Image software-rendering functions (CPU)
RLAPI void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
RLAPI void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
RLAPI void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
RLAPI void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
RLAPI void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
RLAPI void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw a filled circle within an image
RLAPI void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw a filled circle within an image (Vector version)
RLAPI void ImageDrawCircleLines(Image *dst, int centerX, int centerY, int radius, Color color);          // Draw circle outline within an image
RLAPI void ImageDrawCircleLinesV(Image *dst, Vector2 center, int radius, Color color);                   // Draw circle outline within an image (Vector version)
RLAPI void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
RLAPI void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
RLAPI void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                // Draw rectangle within an image
RLAPI void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
RLAPI void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)

// Texture loading functions
// NOTE: These functions require GPU access
RLAPI auto LoadTexture(const char* fileName) -> Texture2D; // Load texture from file into GPU memory (VRAM)
RLAPI auto LoadTextureFromImage(Image image) -> Texture2D; // Load texture from image data
RLAPI auto LoadTextureCubemap(Image image, int layout) -> TextureCubemap; // Load cubemap from image, multiple image cubemap layouts supported
RLAPI auto LoadRenderTexture(int width, int height) -> RenderTexture2D; // Load texture for rendering (framebuffer)
RLAPI auto IsTextureReady(Texture2D texture) -> bool; // Check if a texture is ready
RLAPI void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
RLAPI auto IsRenderTextureReady(RenderTexture2D target) -> bool; // Check if a render texture is ready
RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
RLAPI void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data

// Texture configuration functions
RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode

// Texture drawing functions
RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
RLAPI void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters
RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draws a texture (or part of it) that stretches or shrinks nicely

// Color/pixel related functions
RLAPI auto Fade(Color color, float alpha) -> Color; // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI auto ColorToInt(Color color) -> int; // Get hexadecimal value for a Color
RLAPI auto ColorNormalize(Color color) -> Vector4; // Get Color normalized as float [0..1]
RLAPI auto ColorFromNormalized(Vector4 normalized) -> Color; // Get Color from normalized values [0..1]
RLAPI auto ColorToHSV(Color color) -> Vector3; // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
RLAPI auto ColorFromHSV(float hue, float saturation, float value) -> Color; // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
RLAPI auto ColorTint(Color color, Color tint) -> Color; // Get color multiplied with another color
RLAPI auto ColorBrightness(Color color, float factor) -> Color; // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
RLAPI auto ColorContrast(Color color, float contrast) -> Color; // Get color with contrast correction, contrast values between -1.0f and 1.0f
RLAPI auto ColorAlpha(Color color, float alpha) -> Color; // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI auto ColorAlphaBlend(Color dst, Color src, Color tint) -> Color; // Get src alpha-blended into dst color with tint
RLAPI auto GetColor(unsigned int hexValue) -> Color; // Get Color structure from hexadecimal value
RLAPI auto GetPixelColor(void* srcPtr, int format) -> Color; // Get Color from a source pixel pointer of certain format
RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer
RLAPI auto GetPixelDataSize(int width, int height, int format) -> int; // Get pixel data size in bytes for certain format

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// Font loading/unloading functions
RLAPI auto GetFontDefault(void) -> Font; // Get the default Font
RLAPI auto LoadFont(const char* fileName) -> Font; // Load font from file into GPU memory (VRAM)
RLAPI auto LoadFontEx(const char* fileName, int fontSize, int* fontChars, int glyphCount) -> Font; // Load font from file with extended parameters, use NULL for fontChars and 0 for glyphCount to load the default character set
RLAPI auto LoadFontFromImage(Image image, Color key, int firstChar) -> Font; // Load font from Image (XNA style)
RLAPI auto LoadFontFromMemory(const char* fileType, const unsigned char* fileData, int dataSize, int fontSize, int* fontChars, int glyphCount) -> Font; // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
RLAPI auto IsFontReady(Font font) -> bool; // Check if a font is ready
RLAPI auto LoadFontData(const unsigned char* fileData, int dataSize, int fontSize, int* fontChars, int glyphCount, int type) -> GlyphInfo*; // Load font data for further use
RLAPI auto GenImageFontAtlas(const GlyphInfo* chars, Rectangle** recs, int glyphCount, int fontSize, int padding, int packMethod) -> Image; // Generate image font atlas using chars info
RLAPI void UnloadFontData(GlyphInfo *chars, int glyphCount);                                // Unload font chars info data (RAM)
RLAPI void UnloadFont(Font font);                                                           // Unload font from GPU memory (VRAM)
RLAPI auto ExportFontAsCode(Font font, const char* fileName) -> bool; // Export font as code file, returns true on success

// Text drawing functions
RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int count, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)

// Text font info functions
RLAPI auto MeasureText(const char* text, int fontSize) -> int; // Measure string width for default font
RLAPI auto MeasureTextEx(Font font, const char* text, float fontSize, float spacing) -> Vector2; // Measure string size for Font
RLAPI auto GetGlyphIndex(Font font, int codepoint) -> int; // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
RLAPI auto GetGlyphInfo(Font font, int codepoint) -> GlyphInfo; // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
RLAPI auto GetGlyphAtlasRec(Font font, int codepoint) -> Rectangle; // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

// Text codepoints management functions (unicode characters)
RLAPI auto LoadUTF8(const int* codepoints, int length) -> char*; // Load UTF-8 text encoded from codepoints array
RLAPI void UnloadUTF8(char *text);                                      // Unload UTF-8 text encoded from codepoints array
RLAPI auto LoadCodepoints(const char* text, int* count) -> int*; // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
RLAPI void UnloadCodepoints(int *codepoints);                           // Unload codepoints data from memory
RLAPI auto GetCodepointCount(const char* text) -> int; // Get total number of codepoints in a UTF-8 encoded string
RLAPI auto GetCodepoint(const char* text, int* codepointSize) -> int; // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI auto GetCodepointNext(const char* text, int* codepointSize) -> int; // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI auto GetCodepointPrevious(const char* text, int* codepointSize) -> int; // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI auto CodepointToUTF8(int codepoint, int* utf8Size) -> const char*; // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Text strings management functions (no UTF-8 strings, only byte chars)
// NOTE: Some strings allocate memory internally for returned strings, just be careful!
RLAPI auto TextCopy(char* dst, const char* src) -> int; // Copy one string to another, returns bytes copied
RLAPI auto TextIsEqual(const char* text1, const char* text2) -> bool; // Check if two text string are equal
RLAPI auto TextLength(const char* text) -> unsigned int; // Get text length, checks for '\0' ending
RLAPI auto TextFormat(const char* text, ...) -> const char*; // Text formatting with variables (sprintf() style)
RLAPI auto TextSubtext(const char* text, int position, int length) -> const char*; // Get a piece of a text string
RLAPI auto TextReplace(char* text, const char* replace, const char* by) -> char*; // Replace text string (WARNING: memory must be freed!)
RLAPI auto TextInsert(const char* text, const char* insert, int position) -> char*; // Insert text in a position (WARNING: memory must be freed!)
RLAPI auto TextJoin(const char** textList, int count, const char* delimiter) -> const char*; // Join text strings with delimiter
RLAPI auto TextSplit(const char* text, char delimiter, int* count) -> const char**; // Split text into multiple strings
RLAPI void TextAppend(char *text, const char *append, int *position);                       // Append text at specific position and move cursor!
RLAPI auto TextFindIndex(const char* text, const char* find) -> int; // Find first text occurrence within a string
RLAPI auto TextToUpper(const char* text) -> const char*; // Get upper case version of provided string
RLAPI auto TextToLower(const char* text) -> const char*; // Get lower case version of provided string
RLAPI auto TextToPascal(const char* text) -> const char*; // Get Pascal case notation version of provided string
RLAPI auto TextToInteger(const char* text) -> int; // Get integer value from text (negative values not supported)

//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Basic geometric 3D shapes drawing functions
RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);                                    // Draw a line in 3D world space
RLAPI void DrawPoint3D(Vector3 position, Color color);                                                   // Draw a point in 3D space, actually a small line
RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color); // Draw a circle in 3D world space
RLAPI void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color);                              // Draw a color-filled triangle (vertex in counter-clockwise order!)
RLAPI void DrawTriangleStrip3D(Vector3 *points, int pointCount, Color color);                            // Draw a triangle strip defined by points
RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);             // Draw cube
RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);                                       // Draw cube (Vector version)
RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);        // Draw cube wires
RLAPI void DrawCubeWiresV(Vector3 position, Vector3 size, Color color);                                  // Draw cube wires (Vector version)
RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);                                     // Draw sphere
RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);            // Draw sphere with extended parameters
RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);         // Draw sphere wires
RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone
RLAPI void DrawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color); // Draw a cylinder with base at startPos and top at endPos
RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone wires
RLAPI void DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color); // Draw a cylinder wires with base at startPos and top at endPos
RLAPI void DrawCapsule(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color); // Draw a capsule with the center of its sphere caps at startPos and endPos
RLAPI void DrawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int slices, int rings, Color color); // Draw capsule wireframe with the center of its sphere caps at startPos and endPos
RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);                                      // Draw a plane XZ
RLAPI void DrawRay(Ray ray, Color color);                                                                // Draw a ray line
RLAPI void DrawGrid(int slices, float spacing);                                                          // Draw a grid (centered at (0, 0, 0))

//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Model management functions
RLAPI auto LoadModel(const char* fileName) -> Model; // Load model from files (meshes and materials)
RLAPI auto LoadModelFromMesh(Mesh mesh) -> Model; // Load model from generated mesh (default material)
RLAPI auto IsModelReady(Model model) -> bool; // Check if a model is ready
RLAPI void UnloadModel(Model model);                                                        // Unload model (including meshes) from memory (RAM and/or VRAM)
RLAPI auto GetModelBoundingBox(Model model) -> BoundingBox; // Compute model bounding box limits (considers all meshes)

// Model drawing functions
RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);               // Draw a model (with texture if set)
RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); // Draw a model with extended parameters
RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);          // Draw a model wires (with texture if set)
RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); // Draw a model wires (with texture if set) with extended parameters
RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                   // Draw bounding box (wires)
RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint);   // Draw a billboard texture
RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint); // Draw a billboard texture defined by source
RLAPI void DrawBillboardPro(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint); // Draw a billboard texture defined by source and rotation

// Mesh management functions
RLAPI void UploadMesh(Mesh *mesh, bool dynamic);                                            // Upload mesh vertex data in GPU and provide VAO/VBO ids
RLAPI void UpdateMeshBuffer(Mesh mesh, int index, const void *data, int dataSize, int offset); // Update mesh vertex data in GPU for a specific buffer index
RLAPI void UnloadMesh(Mesh mesh);                                                           // Unload mesh data from CPU and GPU
RLAPI void DrawMesh(Mesh mesh, Material material, Matrix transform);                        // Draw a 3d mesh with material and transform
RLAPI void DrawMeshInstanced(Mesh mesh, Material material, const Matrix *transforms, int instances); // Draw multiple mesh instances with material and different transforms
RLAPI auto ExportMesh(Mesh mesh, const char* fileName) -> bool; // Export mesh data to file, returns true on success
RLAPI auto GetMeshBoundingBox(Mesh mesh) -> BoundingBox; // Compute mesh bounding box limits
RLAPI void GenMeshTangents(Mesh *mesh);                                                     // Compute mesh tangents

// Mesh generation functions
RLAPI auto GenMeshPoly(int sides, float radius) -> Mesh; // Generate polygonal mesh
RLAPI auto GenMeshPlane(float width, float length, int resX, int resZ) -> Mesh; // Generate plane mesh (with subdivisions)
RLAPI auto GenMeshCube(float width, float height, float length) -> Mesh; // Generate cuboid mesh
RLAPI auto GenMeshSphere(float radius, int rings, int slices) -> Mesh; // Generate sphere mesh (standard sphere)
RLAPI auto GenMeshHemiSphere(float radius, int rings, int slices) -> Mesh; // Generate half-sphere mesh (no bottom cap)
RLAPI auto GenMeshCylinder(float radius, float height, int slices) -> Mesh; // Generate cylinder mesh
RLAPI auto GenMeshCone(float radius, float height, int slices) -> Mesh; // Generate cone/pyramid mesh
RLAPI auto GenMeshTorus(float radius, float size, int radSeg, int sides) -> Mesh; // Generate torus mesh
RLAPI auto GenMeshKnot(float radius, float size, int radSeg, int sides) -> Mesh; // Generate trefoil knot mesh
RLAPI auto GenMeshHeightmap(Image heightmap, Vector3 size) -> Mesh; // Generate heightmap mesh from image data
RLAPI auto GenMeshCubicmap(Image cubicmap, Vector3 cubeSize) -> Mesh; // Generate cubes-based map mesh from image data

// Material loading/unloading functions
RLAPI auto LoadMaterials(const char* fileName, int* materialCount) -> Material*; // Load materials from model file
RLAPI auto LoadMaterialDefault(void) -> Material; // Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
RLAPI auto IsMaterialReady(Material material) -> bool; // Check if a material is ready
RLAPI void UnloadMaterial(Material material);                                               // Unload material from GPU memory (VRAM)
RLAPI void SetMaterialTexture(Material *material, int mapType, Texture2D texture);          // Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
RLAPI void SetModelMeshMaterial(Model *model, int meshId, int materialId);                  // Set material for a mesh

// Model animations loading/unloading functions
RLAPI auto LoadModelAnimations(const char* fileName, unsigned int* animCount) -> ModelAnimation*; // Load model animations from file
RLAPI void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);               // Update model animation pose
RLAPI void UnloadModelAnimation(ModelAnimation anim);                                       // Unload animation data
RLAPI void UnloadModelAnimations(ModelAnimation *animations, unsigned int count);           // Unload animation array data
RLAPI auto IsModelAnimationValid(Model model, ModelAnimation anim) -> bool; // Check model animation skeleton match

// Collision detection functions
RLAPI auto CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2) -> bool; // Check collision between two spheres
RLAPI auto CheckCollisionBoxes(BoundingBox box1, BoundingBox box2) -> bool; // Check collision between two bounding boxes
RLAPI auto CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius) -> bool; // Check collision between box and sphere
RLAPI auto GetRayCollisionSphere(Ray ray, Vector3 center, float radius) -> RayCollision; // Get collision info between ray and sphere
RLAPI auto GetRayCollisionBox(Ray ray, BoundingBox box) -> RayCollision; // Get collision info between ray and box
RLAPI auto GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform) -> RayCollision; // Get collision info between ray and mesh
RLAPI auto GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3) -> RayCollision; // Get collision info between ray and triangle
RLAPI auto GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4) -> RayCollision; // Get collision info between ray and quad

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

// Audio device management functions
RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
RLAPI auto IsAudioDeviceReady(void) -> bool; // Check if audio device has been initialized successfully
RLAPI void SetMasterVolume(float volume);                             // Set master volume (listener)

// Wave/Sound loading/unloading functions
RLAPI auto LoadWave(const char* fileName) -> Wave; // Load wave data from file
RLAPI auto LoadWaveFromMemory(const char* fileType, const unsigned char* fileData, int dataSize) -> Wave; // Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
RLAPI auto IsWaveReady(Wave wave) -> bool; // Checks if wave data is ready
RLAPI auto LoadSound(const char* fileName) -> Sound; // Load sound from file
RLAPI auto LoadSoundFromWave(Wave wave) -> Sound; // Load sound from wave data
RLAPI auto IsSoundReady(Sound sound) -> bool; // Checks if a sound is ready
RLAPI void UpdateSound(Sound sound, const void *data, int sampleCount); // Update sound buffer with new data
RLAPI void UnloadWave(Wave wave);                                     // Unload wave data
RLAPI void UnloadSound(Sound sound);                                  // Unload sound
RLAPI auto ExportWave(Wave wave, const char* fileName) -> bool; // Export wave data to file, returns true on success
RLAPI auto ExportWaveAsCode(Wave wave, const char* fileName) -> bool; // Export wave sample data to code (.h), returns true on success

// Wave/Sound management functions
RLAPI void PlaySound(Sound sound);                                    // Play a sound
RLAPI void StopSound(Sound sound);                                    // Stop playing a sound
RLAPI void PauseSound(Sound sound);                                   // Pause a sound
RLAPI void ResumeSound(Sound sound);                                  // Resume a paused sound
RLAPI auto IsSoundPlaying(Sound sound) -> bool; // Check if a sound is currently playing
RLAPI void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
RLAPI void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)
RLAPI void SetSoundPan(Sound sound, float pan);                       // Set pan for a sound (0.5 is center)
RLAPI auto WaveCopy(Wave wave) -> Wave; // Copy a wave to a new wave
RLAPI void WaveCrop(Wave *wave, int initSample, int finalSample);     // Crop a wave to defined samples range
RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels); // Convert wave data to desired format
RLAPI auto LoadWaveSamples(Wave wave) -> float*; // Load samples data from wave as a 32bit float data array
RLAPI void UnloadWaveSamples(float *samples);                         // Unload samples data loaded with LoadWaveSamples()

// Music management functions
RLAPI auto LoadMusicStream(const char* fileName) -> Music; // Load music stream from file
RLAPI auto LoadMusicStreamFromMemory(const char* fileType, const unsigned char* data, int dataSize) -> Music; // Load music stream from data
RLAPI auto IsMusicReady(Music music) -> bool; // Checks if a music stream is ready
RLAPI void UnloadMusicStream(Music music);                            // Unload music stream
RLAPI void PlayMusicStream(Music music);                              // Start music playing
RLAPI auto IsMusicStreamPlaying(Music music) -> bool; // Check if music is playing
RLAPI void UpdateMusicStream(Music music);                            // Updates buffers for music streaming
RLAPI void StopMusicStream(Music music);                              // Stop music playing
RLAPI void PauseMusicStream(Music music);                             // Pause music playing
RLAPI void ResumeMusicStream(Music music);                            // Resume playing paused music
RLAPI void SeekMusicStream(Music music, float position);              // Seek music to a position (in seconds)
RLAPI void SetMusicVolume(Music music, float volume);                 // Set volume for music (1.0 is max level)
RLAPI void SetMusicPitch(Music music, float pitch);                   // Set pitch for a music (1.0 is base level)
RLAPI void SetMusicPan(Music music, float pan);                       // Set pan for a music (0.5 is center)
RLAPI auto GetMusicTimeLength(Music music) -> float; // Get music time length (in seconds)
RLAPI auto GetMusicTimePlayed(Music music) -> float; // Get current music time played (in seconds)

// AudioStream management functions
RLAPI auto LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels) -> AudioStream; // Load audio stream (to stream raw audio pcm data)
RLAPI auto IsAudioStreamReady(AudioStream stream) -> bool; // Checks if an audio stream is ready
RLAPI void UnloadAudioStream(AudioStream stream);                     // Unload audio stream and free memory
RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int frameCount); // Update audio stream buffers with data
RLAPI auto IsAudioStreamProcessed(AudioStream stream) -> bool; // Check if any audio stream buffers requires refill
RLAPI void PlayAudioStream(AudioStream stream);                       // Play audio stream
RLAPI void PauseAudioStream(AudioStream stream);                      // Pause audio stream
RLAPI void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
RLAPI auto IsAudioStreamPlaying(AudioStream stream) -> bool; // Check if audio stream is playing
RLAPI void StopAudioStream(AudioStream stream);                       // Stop audio stream
RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);    // Set volume for audio stream (1.0 is max level)
RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
RLAPI void SetAudioStreamPan(AudioStream stream, float pan);          // Set pan for audio stream (0.5 is centered)
RLAPI void SetAudioStreamBufferSizeDefault(int size);                 // Default size for new audio streams
RLAPI void SetAudioStreamCallback(AudioStream stream, AudioCallback callback);  // Audio thread callback to request new data

RLAPI void AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Attach audio stream processor to stream
RLAPI void DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Detach audio stream processor from stream

RLAPI void AttachAudioMixedProcessor(AudioCallback processor); // Attach audio stream processor to the entire audio pipeline
RLAPI void DetachAudioMixedProcessor(AudioCallback processor); // Detach audio stream processor from the entire audio pipeline

#if defined(__cplusplus)
}
#endif

#endif // RAYLIB_H
