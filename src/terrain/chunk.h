#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>
#include "block.h"

namespace mc
{
    class Chunk;
};

#include "world.h"
#include <vector>
#include <algorithm>
using std::vector;

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

        void addUV(float u, float v)
        {
            uvCoordinates.push_back(u);
            uvCoordinates.push_back(v);
        }

        void addNormal(float x, float y, float z)
        {
            normals.push_back(x);
            normals.push_back(y);
            normals.push_back(z);
        }
        // vector<Texture> textures;
    };

    class Chunk
    {
    public:
        static const int CHUNK_SIZE = 16;
        static const int CHUNK_HEIGHT = 60;

    private:
        World *world;
        // BlockType ***blocks;
        BlockType blocks[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE] = {BlockType::Air};
        // BlockType blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE] = {BlockType::Stone};
        Mesh mesh;
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::mat4 modelMatrix = glm::mat4(1.0);

        GLuint vertexArrayID;
        mc::VBO vertexBuffer;
        mc::VBO uvBuffer;
        mc::VBO indicesBuffer;
        mc::VBO normalsBuffer;
        GLuint skyboxTexture;

        mc::Texture tex = mc::createTextureFromPath("../assets/stone.jpg");
        mc::Texture tex2 = mc::createTextureFromPath("../assets/endstone.png");

    public:
        Chunk();
        ~Chunk();
        void update();
        void render(const std::unique_ptr<Shader> &shader);
        void createMesh();
        int get1DIndexForPosition(glm::vec3 position);
        glm::vec3 getPosition() { return position; }
        BlockType getBlock(glm::ivec3 position) { return blocks[position.x][position.y][position.z]; }

        void setBlock(glm::ivec3 position, BlockType bType) { blocks[position.x][position.y][position.z] = bType; }
        void setPosition(glm::vec3 pos) { position = pos; }
        void setWorld(World *w) { world = w; }
    };

}; // namespace mc

#endif