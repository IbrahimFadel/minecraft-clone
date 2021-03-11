#include "chunk.h"

using namespace mc;

// Chunk::Chunk() : blocks(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, Block()){
Chunk::Chunk(){

    // blocks = new BlockType[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    // blocks = (BlockType *)malloc(sizeof(BlockType) * CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
    // blocks = new Block **[CHUNK_SIZE];
    // for (int i = 0; i < CHUNK_SIZE; i++)
    // {
    //     blocks[i] = new Block *[CHUNK_SIZE];
    //     for (int j = 0; j < CHUNK_SIZE; j++)
    //     {
    //         blocks[i][j] = new Block[CHUNK_SIZE];
    //         for (int k = 0; k < CHUNK_SIZE; k++)
    //         {
    //             blocks[i][j][k] = Block();
    //         }
    //     }
    // }
    // blocks = new BlockType[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

    // blocks = blockAllocator.allocate(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
    // blockAllocator.construct(blocks);
    // blocks = (Block *)malloc(sizeof(Block) * (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE));
    // blocks->Block();
};

Chunk::~Chunk()
{
    // delete blocks;
    // blockAllocator.destroy(blocks);
    // blockAllocator.deallocate(blocks, CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
}

void Chunk::createMesh()
{
    int size = 0;
    glm::ivec3 start(0, 0, 0);

    for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
        {
            for (int y = 0; y < Chunk::CHUNK_HEIGHT; y++)
            {
                BlockType value = getBlock(glm::vec3(x, y, z));

                if (value != BlockType::Air)
                {
                    //Base
                    float ix = x + start.x;
                    float iy = y + start.y;
                    float iz = z + start.z;

                    //Positive
                    float px = 0.5f + ix;
                    float py = 0.5f + iy;
                    float pz = 0.5f + iz;

                    //Negative
                    float nx = ix - 0.5f;
                    float ny = iy - 0.5f;
                    float nz = iz - 0.5f;

                    //Top face
                    if (y == Chunk::CHUNK_SIZE - 1 || getBlock(glm::vec3(x, y + 1, z)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size + 1); // 1 5 9
                        mesh.indices.push_back(size);     // 0 4 8
                        mesh.indices.push_back(size + 2); // 2 6 10
                        mesh.indices.push_back(size + 1); // 1 5 9
                        mesh.indices.push_back(size + 2); // 2 6 10
                        mesh.indices.push_back(size + 3); // 3 7 11

                        mesh.addVertex(nx, py, pz); // front top left
                        mesh.addVertex(nx, py, nz); // back top left
                        mesh.addVertex(px, py, pz); // front top right
                        mesh.addVertex(px, py, nz); // back top right

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(0.0, 1.0, 0.0);
                        mesh.addNormal(0.0, 1.0, 0.0);
                        mesh.addNormal(0.0, 1.0, 0.0);
                        mesh.addNormal(0.0, 1.0, 0.0); // Top Side

                        size += 4;
                    }

                    //Bottom face
                    if (y == 0 || getBlock(glm::vec3(x, y - 1, z)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size + 1);
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 2);

                        mesh.addVertex(px, ny, pz);
                        mesh.addVertex(px, ny, nz);
                        mesh.addVertex(nx, ny, pz);
                        mesh.addVertex(nx, ny, nz);

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(0.0, -1.0, 0.0);
                        mesh.addNormal(0.0, -1.0, 0.0);
                        mesh.addNormal(0.0, -1.0, 0.0);
                        mesh.addNormal(0.0, -1.0, 0.0); // Bottom side
                        size += 4;
                    }

                    //Front face
                    if (z == Chunk::CHUNK_SIZE - 1 || getBlock(glm::vec3(x, y, z + 1)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size + 1);

                        mesh.addVertex(nx, ny, pz);
                        mesh.addVertex(nx, py, pz);
                        mesh.addVertex(px, ny, pz);
                        mesh.addVertex(px, py, pz);

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(0.0, 0.0, 1.0);
                        mesh.addNormal(0.0, 0.0, 1.0);
                        mesh.addNormal(0.0, 0.0, 1.0);
                        mesh.addNormal(0.0, 0.0, 1.0); // Front Side

                        size += 4;
                    }

                    //Back face
                    if (z == 0 || getBlock(glm::vec3(x, y, z - 1)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size + 1);
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 1);
                        mesh.indices.push_back(size);

                        mesh.addVertex(px, ny, nz);
                        mesh.addVertex(px, py, nz);
                        mesh.addVertex(nx, ny, nz);
                        mesh.addVertex(nx, py, nz);

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(0.0, 0.0, -1.0);
                        mesh.addNormal(0.0, 0.0, -1.0);
                        mesh.addNormal(0.0, 0.0, -1.0);
                        mesh.addNormal(0.0, 0.0, -1.0); // Back Side

                        size += 4;
                    }

                    //Right face
                    if (x == Chunk::CHUNK_SIZE - 1 || getBlock(glm::vec3(x + 1, y, z)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size + 1);
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 1);
                        mesh.indices.push_back(size);

                        mesh.addVertex(px, ny, pz);
                        mesh.addVertex(px, py, pz);
                        mesh.addVertex(px, ny, nz);
                        mesh.addVertex(px, py, nz);

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(1.0, 0.0, 0.0);
                        mesh.addNormal(1.0, 0.0, 0.0);
                        mesh.addNormal(1.0, 0.0, 0.0);
                        mesh.addNormal(1.0, 0.0, 0.0); // Right Side

                        size += 4;
                    }

                    //Left face
                    if (x == 0 || getBlock(glm::vec3(x - 1, y, z)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 2);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size);
                        mesh.indices.push_back(size + 3);
                        mesh.indices.push_back(size + 1);

                        mesh.addVertex(nx, ny, nz);
                        mesh.addVertex(nx, py, nz);
                        mesh.addVertex(nx, ny, pz);
                        mesh.addVertex(nx, py, pz);

                        mesh.addUV(0, 0);
                        mesh.addUV(1, 0);
                        mesh.addUV(0, 1);
                        mesh.addUV(1, 1);

                        mesh.addNormal(-1.0, 0.0, 0.0);
                        mesh.addNormal(-1.0, 0.0, 0.0);
                        mesh.addNormal(-1.0, 0.0, 0.0);
                        mesh.addNormal(-1.0, 0.0, 0.0); // Left Side

                        size += 4;
                    }
                }
            }
        }
    }

    vertexArrayID = mc::createVAO();
    mc::bindVAO(vertexArrayID);

    vertexBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    mc::bindVBO(vertexBuffer);
    mc::vboBuffer(vertexBuffer, sizeof(mesh.vertices[0]) * mesh.vertices.size(), &mesh.vertices[0]);

    uvBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    mc::bindVBO(uvBuffer);
    mc::vboBuffer(uvBuffer, sizeof(mesh.uvCoordinates[0]) * mesh.uvCoordinates.size(), &mesh.uvCoordinates[0]);

    indicesBuffer = mc::createVBO(GL_ELEMENT_ARRAY_BUFFER);
    mc::bindVBO(indicesBuffer);
    mc::vboBuffer(indicesBuffer, sizeof(mesh.indices[0]) * mesh.indices.size(), &mesh.indices[0]);

    normalsBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    mc::bindVBO(normalsBuffer);
    mc::vboBuffer(normalsBuffer, sizeof(mesh.normals[0]) * mesh.normals.size(), &mesh.normals[0]);
}

void Chunk::render(const std::unique_ptr<Shader> &shader)
{
    GLuint textureID = glGetUniformLocation(shader->getProgramID(), "textureSampler");
    GLuint modelID = glGetUniformLocation(shader->getProgramID(), "model");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.handle);
    glUniform1i(textureID, 0);

    modelMatrix[3][0] = position.x * CHUNK_SIZE;
    modelMatrix[3][1] = position.y * CHUNK_SIZE;
    modelMatrix[3][2] = position.z * CHUNK_SIZE;

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

    mc::bindVAO(vertexArrayID);
    mc::bindVBO(vertexBuffer);
    mc::vaoEnable(0, 3, GL_FLOAT, 0, 0);

    mc::bindVBO(uvBuffer);
    mc::vaoEnable(1, 2, GL_FLOAT, 0, 0);

    mc::bindVBO(normalsBuffer);
    mc::vaoEnable(2, 3, GL_FLOAT, 0, 0);

    glDrawElements(
        GL_TRIANGLES,
        mesh.indices.size(),
        GL_UNSIGNED_INT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

// void Chunk::setBlock(glm::ivec3 position, BlockType bType)
// {
//     blocks[position.x][position.y][position.z] = bType;
//     // int newIndex = get1DIndexForPosition(position);
//     // blocks[newIndex] = bType;
// }

// void Chunk::addCubeToMesh(float x, float y, float z)
// {
//     auto factor = mesh.vertices.size() / 3;

//     mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);
//     mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);

//     mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);

//     mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);
//     mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);

//     mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
//     mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);
//     mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);

//     mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);
//     mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);
//     mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);

//     mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
//     mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
//     mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);

//     mesh.addIndices(factor + 0, factor + 1, factor + 2, factor + 2, factor + 1, factor + 3);
//     mesh.addIndices(factor + 4, factor + 5, factor + 6, factor + 6, factor + 5, factor + 7);
//     mesh.addIndices(factor + 8, factor + 9, factor + 10, factor + 10, factor + 9, factor + 11);
//     mesh.addIndices(factor + 12, factor + 13, factor + 14, factor + 14, factor + 13, factor + 15);
//     mesh.addIndices(factor + 16, factor + 17, factor + 18, factor + 18, factor + 17, factor + 19);
//     mesh.addIndices(factor + 20, factor + 21, factor + 22, factor + 22, factor + 21, factor + 23);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addUV(0, 0);
//     mesh.addUV(1, 0);
//     mesh.addUV(0, 1);
//     mesh.addUV(1, 1);

//     mesh.addNormal(0.0, 0.0, 1.0);
//     mesh.addNormal(0.0, 0.0, 1.0);
//     mesh.addNormal(0.0, 0.0, 1.0);
//     mesh.addNormal(0.0, 0.0, 1.0); // Front Side
//     mesh.addNormal(1.0, 0.0, 0.0);
//     mesh.addNormal(1.0, 0.0, 0.0);
//     mesh.addNormal(1.0, 0.0, 0.0);
//     mesh.addNormal(1.0, 0.0, 0.0); // Right Side
//     mesh.addNormal(0.0, 0.0, -1.0);
//     mesh.addNormal(0.0, 0.0, -1.0);
//     mesh.addNormal(0.0, 0.0, -1.0);
//     mesh.addNormal(0.0, 0.0, -1.0); // Back Side
//     mesh.addNormal(-1.0, 0.0, 0.0);
//     mesh.addNormal(-1.0, 0.0, 0.0);
//     mesh.addNormal(-1.0, 0.0, 0.0);
//     mesh.addNormal(-1.0, 0.0, 0.0); // Left Side
//     mesh.addNormal(0.0, 1.0, 0.0);
//     mesh.addNormal(0.0, 1.0, 0.0);
//     mesh.addNormal(0.0, 1.0, 0.0);
//     mesh.addNormal(0.0, 1.0, 0.0); // Top Side
//     mesh.addNormal(0.0, -1.0, 0.0);
//     mesh.addNormal(0.0, -1.0, 0.0);
//     mesh.addNormal(0.0, -1.0, 0.0);
//     mesh.addNormal(0.0, -1.0, 0.0); // Bottom side
// }