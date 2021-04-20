#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "block.h"
#include "shader.h"

namespace mc
{
    struct Mesh;
    class Chunk;
}; // namespace mc

#include "texture.h"
#include "world.h"
#include <vector>
#include <algorithm>
using std::vector;

#include <GL/glew.h>

namespace mc
{
    struct Vertex
    {
    };

    struct Mesh
    {
        vector<float> vertices;
        vector<unsigned int> indices;
        vector<float> uvCoordinates;
        vector<float> normals;

        void addVertex(float x, float y, float z)
        {
            vertices.insert(vertices.end(), {x, y, z});
        };

        void addIndices(unsigned short i0, unsigned short i1, unsigned short i2, unsigned short i3, unsigned short i4, unsigned short i5)
        {
            indices.push_back(i0);
            indices.push_back(i1);
            indices.push_back(i2);
            indices.push_back(i3);
            indices.push_back(i4);
            indices.push_back(i5);
        }

        void addUV(glm::vec2 uv)
        {
            uvCoordinates.push_back(uv.x);
            uvCoordinates.push_back(uv.y);
        }

        void addNormal(float x, float y, float z)
        {
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
        }
    };

    class Chunk
    {
    public:
        static const int CHUNK_SIZE = 16;
        static const int CHUNK_HEIGHT = 60;

    private:
        World *world;
        BlockType blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE] = {BlockType::Air};
        Mesh *blockMesh = new Mesh();
        Mesh *waterMesh = new Mesh();
        int blockMeshSize = 0;
        int waterMeshSize = 0;

        glm::ivec2 position = glm::ivec2(0, 0);
        glm::mat4 modelMatrix = glm::mat4(1.0);

        GLuint blockMeshVertexArrayID;
        GLuint blockMeshVertexBuffer;
        GLuint blockMeshUvBuffer;
        GLuint blockMeshIndicesBuffer;
        GLuint blockMeshNormalsBuffer;

        GLuint waterMeshVertexArrayID;
        GLuint waterMeshVertexBuffer;
        GLuint waterMeshUvBuffer;
        GLuint waterMeshIndicesBuffer;
        GLuint waterMeshNormalsBuffer;

        mc::Texture blockatlasTexture = mc::createTextureFromPath("../assets/blockatlas.png");

        void addCubeToMesh(glm::vec3 cubePos, BlockType type, Mesh *mesh, int *meshSize);

    public:
        void update();
        void renderBlockMesh(const std::unique_ptr<Shader> &shader);
        void renderWaterMesh(const std::unique_ptr<Shader> &shader);
        void createMesh();

        glm::ivec2 getPosition() { return position; }
        BlockType getBlock(glm::ivec3 position) { return blocks[position.x][position.y][position.z]; }

        void setBlock(glm::ivec3 position, BlockType bType) { blocks[position.x][position.y][position.z] = bType; }
        void setPosition(glm::ivec2 pos) { position = pos; }
        void setWorld(World *w) { world = w; }
    };

}; // namespace mc

#endif