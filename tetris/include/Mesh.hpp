#ifndef RAYLIB_CPP_INCLUDE_MESH_HPP_
#define RAYLIB_CPP_INCLUDE_MESH_HPP_

#include <string>
#include <vector>

#include "./raylib.hpp"
#include "./raylib-cpp-utils.hpp"
#include "./BoundingBox.hpp"
#include "./Model.hpp"

namespace raylib {
/**
 * Vertex data definning a mesh
 */
class Mesh : public ::Mesh {
 public:
    Mesh(const ::Mesh& mesh) {
        set(mesh);
    }

    /**
     * Load meshes from model file
     */
    // static std::vector<Mesh> Load(const std::string& fileName) {
    //    int count = 0;
    //    ::Mesh* meshes = LoadMeshes(fileName.c_str(), &count);
    //    return std::vector<Mesh>(meshes, meshes + count);
    // }

    Mesh(const Mesh&) = delete;

    Mesh(Mesh&& other) {
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;
    }

    /**
     * Generate polygonal mesh
     */
    static auto Poly(int sides, float radius) -> ::Mesh
    {
        return ::GenMeshPoly(sides, radius);
    }

    /**
     * Generate plane mesh (with subdivisions)
     */
    static auto Plane(float width, float length, int resX, int resZ) -> ::Mesh
    {
        return ::GenMeshPlane(width, length, resX, resZ);
    }

    /**
     * Generate cuboid mesh
     */
    static auto Cube(float width, float height, float length) -> ::Mesh
    {
        return ::GenMeshCube(width, height, length);
    }

    /**
     * Generate sphere mesh (standard sphere)
     */
    static auto Sphere(float radius, int rings, int slices) -> ::Mesh
    {
        return ::GenMeshSphere(radius, rings, slices);
    }

    /**
     * Generate half-sphere mesh (no bottom cap)
     */
    static auto HemiSphere(float radius, int rings, int slices) -> ::Mesh
    {
        return ::GenMeshHemiSphere(radius, rings, slices);
    }

    /**
     * Generate cylinder mesh
     */
    static auto Cylinder(float radius, float height, int slices) -> ::Mesh
    {
        return ::GenMeshCylinder(radius, height, slices);
    }

    /**
     * Generate cone/pyramid mesh
     */
    static auto Cone(float radius, float height, int slices) -> ::Mesh
    {
        return ::GenMeshCone(radius, height, slices);
    }

    /**
     * Generate torus mesh
     */
    static auto Torus(float radius, float size, int radSeg, int sides) -> ::Mesh
    {
        return ::GenMeshTorus(radius, size, radSeg, sides);
    }

    /**
     * Generate trefoil knot mesh
     */
    static auto Knot(float radius, float size, int radSeg, int sides) -> ::Mesh
    {
        return ::GenMeshKnot(radius, size, radSeg, sides);
    }

    /**
     * Generate heightmap mesh from image data
     */
    static auto Heightmap(const ::Image& heightmap, ::Vector3 size) -> ::Mesh
    {
        return ::GenMeshHeightmap(heightmap, size);
    }

    /**
     * Generate cubes-based map mesh from image data
     */
    static auto Cubicmap(const ::Image& cubicmap, ::Vector3 cubeSize) -> ::Mesh
    {
        return ::GenMeshCubicmap(cubicmap, cubeSize);
    }

    GETTERSETTER(int, VertexCount, vertexCount)
    GETTERSETTER(int, TriangleCount, triangleCount)
    GETTERSETTER(float*, Vertices, vertices)
    GETTERSETTER(float *, TexCoords, texcoords)
    GETTERSETTER(float *, TexCoords2, texcoords2)
    GETTERSETTER(float *, Normals, normals)
    GETTERSETTER(float *, Tangents, tangents)
    GETTERSETTER(unsigned char *, Colors, colors)
    GETTERSETTER(unsigned short *, Indices, indices) // NOLINT
    GETTERSETTER(float *, AnimVertices, animVertices)
    GETTERSETTER(float *, AnimNormals, animNormals)
    GETTERSETTER(unsigned char *, BoneIds, boneIds)
    GETTERSETTER(float *, BoneWeights, boneWeights)
    GETTERSETTER(unsigned int, VaoId, vaoId)
    GETTERSETTER(unsigned int *, VboId, vboId)

    auto operator=(const ::Mesh& mesh) -> Mesh&
    {
        set(mesh);
        return *this;
    }

    auto operator=(const Mesh&) -> Mesh& = delete;

    auto operator=(Mesh&& other) noexcept -> Mesh&
    {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.vertexCount = 0;
        other.triangleCount = 0;
        other.vertices = nullptr;
        other.texcoords = nullptr;
        other.texcoords2 = nullptr;
        other.normals = nullptr;
        other.tangents = nullptr;
        other.colors = nullptr;
        other.indices = nullptr;
        other.animVertices = nullptr;
        other.animNormals = nullptr;
        other.boneIds = nullptr;
        other.boneWeights = nullptr;
        other.vaoId = 0;
        other.vboId = nullptr;

        return *this;
    }

    ~Mesh() {
        Unload();
    }

    /**
     * Upload mesh vertex data to GPU (VRAM)
     */
    inline void Upload(bool dynamic = false) {
        ::UploadMesh(this, dynamic);
    }

    /**
     * Upload mesh vertex data to GPU (VRAM)
     */
    inline void UpdateBuffer(int index, void *data, int dataSize, int offset = 0) {
        ::UpdateMeshBuffer(*this, index, data, dataSize, offset);
    }

    /**
     * Draw a 3d mesh with material and transform
     */
    inline void Draw(const ::Material& material, const ::Matrix& transform) const {
        ::DrawMesh(*this, material, transform);
    }

    /**
     * Draw multiple mesh instances with material and different transforms
     */
    inline void Draw(const ::Material& material, ::Matrix* transforms, int instances) const {
        ::DrawMeshInstanced(*this, material, transforms, instances);
    }

    /**
     * Export mesh data to file
     *
     * @throws raylib::RaylibException Throws if failed to export the Mesh.
     */
    inline void Export(const std::string& fileName) {
        if (!::ExportMesh(*this, fileName.c_str())) {
            throw new RaylibException("Failed to export the Mesh");
        }
    }

    /**
     * Unload mesh from memory (RAM and/or VRAM)
     */
    inline void Unload() {
        if (vboId != nullptr) {
            ::UnloadMesh(*this);
            vboId = nullptr;
        }
    }

    /**
     * Compute mesh bounding box limits
     */
    inline auto BoundingBox() const -> raylib::BoundingBox
    {
        return ::GetMeshBoundingBox(*this);
    }

    /**
     * Compute mesh bounding box limits
     */
    operator raylib::BoundingBox() {
        return BoundingBox();
    }

    /**
     * Compute mesh tangents
     */
    inline auto GenTangents() -> Mesh&
    {
        ::GenMeshTangents(this);
        return *this;
    }

    /**
     * Load model from generated mesh
     */
    inline auto LoadModelFrom() const -> raylib::Model
    {
        return ::LoadModelFromMesh(*this);
    }

    /**
     * Load model from generated mesh
     */
    operator raylib::Model() {
        return ::LoadModelFromMesh(*this);
    }

 private:
    void set(const ::Mesh& mesh) {
        vertexCount = mesh.vertexCount;
        triangleCount = mesh.triangleCount;
        vertices = mesh.vertices;
        texcoords = mesh.texcoords;
        texcoords2 = mesh.texcoords2;
        normals = mesh.normals;
        tangents = mesh.tangents;
        colors = mesh.colors;
        indices = mesh.indices;
        animVertices = mesh.animVertices;
        animNormals = mesh.animNormals;
        boneIds = mesh.boneIds;
        boneWeights = mesh.boneWeights;
        vaoId = mesh.vaoId;
        vboId = mesh.vboId;
    }
};
}  // namespace raylib

using RMesh = raylib::Mesh;

#endif  // RAYLIB_CPP_INCLUDE_MESH_HPP_
