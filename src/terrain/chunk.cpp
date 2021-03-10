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
    // std::cout << "X from " << position.x * CHUNK_SIZE << " TO " << position.x * CHUNK_SIZE + CHUNK_SIZE << '\n';
    // int notNeeded = 0;
    // for (int x = 0; x < CHUNK_SIZE; x++)
    // {
    //     for (int y = 0; y < CHUNK_SIZE; y++)
    //     {
    //         for (int z = 0; z < CHUNK_SIZE; z++)
    //         {
    //             if (blockCoordinatesAtChunkBorder(x, y, z))
    //             {
    //                 addCubeToMesh((float)x, (float)y, (float)z);
    //             }
    //         }
    //     }
    // }

    addCubeToMesh((float)0, (float)0, (float)0);

    // ! 2730 is the max number of cubes before it breaks
    //? 196560 Vertex vals  196632
    //? 98280 Index vals
    //? 131040 UV vals
    //? 196560 Normal vals

    // addCubeToMesh(0, 0, 0);

    // addCubeToMesh((float)10, (float)10, (float)10);

    // for (int i = 0; i < 2730; i++)
    // // for (int i = 0; i < 5000; i++)
    // {
    //     auto res = OnedTo3d(i);
    //     // std::cout << res[0] << '/' << res[1] << '/' << res[2] << '\n';
    //     addCubeToMesh((float)res[0], (float)res[1], (float)res[2]);
    // }
    // for (int x = 0; x < CHUNK_SIZE; x++)
    // {
    //     for (int y = 0; y < CHUNK_SIZE; y++)
    //     {
    //         for (int z = 0; z < CHUNK_SIZE; z++)
    //         {
    //             addCubeToMesh((float)x, (float)y, (float)z);
    //         }
    //     }
    // }

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

    std::cout << mesh.vertices.size() << '\n';
    std::cout << mesh.indices.size() << '\n';
    std::cout << mesh.uvCoordinates.size() << '\n';
    std::cout << mesh.normals.size() << '\n';
}

int *Chunk::OnedTo3d(int idx)
{
    const int z = idx / (CHUNK_SIZE * CHUNK_SIZE);
    idx -= (z * CHUNK_SIZE * CHUNK_SIZE);
    const int y = idx / CHUNK_SIZE;
    const int x = idx % CHUNK_SIZE;
    int *arr = new int[3];
    // return new int[]{x, y, z};
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    return arr;
}

bool Chunk::blockBordersNeighbourChunk(glm::vec3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;
    if (x == CHUNK_SIZE - 1)
    {
        Chunk *neighbourChunk = world->getChunk(glm::vec3(position.x + 1, position.y, position.z));
        if (neighbourChunk != nullptr)
        {
            BlockType neighbourBlock = neighbourChunk->getBlock(glm::vec3(0, y, z));
            if (neighbourBlock == BlockType::Air)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else if (x == 0)
    {
        Chunk *neighbourChunk = world->getChunk(glm::vec3(position.x - 1, position.y, position.z));
        if (neighbourChunk)
        {
            BlockType neighbourBlock = neighbourChunk->getBlock(glm::vec3(CHUNK_SIZE - 1, y, z));
            if (neighbourBlock == BlockType::Air)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }

    if (z == CHUNK_SIZE - 1)
    {
        Chunk *neighbourChunk = world->getChunk(glm::vec3(position.x, position.y, position.z + 1));
        if (neighbourChunk != nullptr)
        {
            BlockType neighbourBlock = neighbourChunk->getBlock(glm::vec3(z, y, 0));
            if (neighbourBlock == BlockType::Air)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else if (z == 0)
    {
        Chunk *neighbourChunk = world->getChunk(glm::vec3(position.x, position.y, position.z - 1));
        if (neighbourChunk)
        {
            BlockType neighbourBlock = neighbourChunk->getBlock(glm::vec3(x, y, CHUNK_SIZE - 1));
            if (neighbourBlock == BlockType::Air)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool Chunk::blockCoordinatesAtChunkBorder(int x, int y, int z)
{
    int chunkX = (position.x * CHUNK_SIZE);
    int chunkY = (position.y * CHUNK_SIZE);
    int chunkZ = (position.z * CHUNK_SIZE);

    bool bordersNeighbourChunk = blockBordersNeighbourChunk(glm::vec3(x, y, z));
    if (bordersNeighbourChunk)
        return true;

    BlockType front = blocks[get1DIndexForPosition(glm::vec3(x, y, z + 1))];

    BlockType right = blocks[get1DIndexForPosition(glm::vec3(x + 1, y, z))];
    BlockType back = blocks[get1DIndexForPosition(glm::vec3(x, y, z - 1))];
    BlockType left = blocks[get1DIndexForPosition(glm::vec3(x - 1, y, z))];
    BlockType top = blocks[get1DIndexForPosition(glm::vec3(x, y + 1, z))];
    BlockType bottom = blocks[get1DIndexForPosition(glm::vec3(x, y - 1, z))];

    if (front == BlockType::Air || right == BlockType::Air || back == BlockType::Air || left == BlockType::Air || top == BlockType::Air || bottom == BlockType::Air)
    {
        return true;
    }
    return (x == chunkX || y == chunkY || z == chunkZ || x == chunkX + CHUNK_SIZE - 1 || y == chunkY + CHUNK_SIZE - 1 || z == chunkZ + CHUNK_SIZE - 1);
}

int Chunk::get1DIndexForPosition(glm::vec3 position)
{
    return position.x + CHUNK_SIZE * (position.y + CHUNK_SIZE * position.z);
}

void Chunk::addCubeToMesh(float x, float y, float z)
{
    auto factor = mesh.vertices.size() / 3;

    mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);
    mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);

    mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);

    mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);
    mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);

    mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
    mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);
    mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);

    mesh.addVertex(x - blockSize, y + blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z + blockSize);
    mesh.addVertex(x - blockSize, y + blockSize, z - blockSize);
    mesh.addVertex(x + blockSize, y + blockSize, z - blockSize);

    mesh.addVertex(x - blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x + blockSize, y - blockSize, z - blockSize);
    mesh.addVertex(x - blockSize, y - blockSize, z + blockSize);
    mesh.addVertex(x + blockSize, y - blockSize, z + blockSize);

    mesh.addIndices(factor + 0, factor + 1, factor + 2, factor + 2, factor + 1, factor + 3);
    mesh.addIndices(factor + 4, factor + 5, factor + 6, factor + 6, factor + 5, factor + 7);
    mesh.addIndices(factor + 8, factor + 9, factor + 10, factor + 10, factor + 9, factor + 11);
    mesh.addIndices(factor + 12, factor + 13, factor + 14, factor + 14, factor + 13, factor + 15);
    mesh.addIndices(factor + 16, factor + 17, factor + 18, factor + 18, factor + 17, factor + 19);
    mesh.addIndices(factor + 20, factor + 21, factor + 22, factor + 22, factor + 21, factor + 23);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addUV(0, 0);
    mesh.addUV(1, 0);
    mesh.addUV(0, 1);
    mesh.addUV(1, 1);

    mesh.addNormal(0.0, 0.0, 1.0);
    mesh.addNormal(0.0, 0.0, 1.0);
    mesh.addNormal(0.0, 0.0, 1.0);
    mesh.addNormal(0.0, 0.0, 1.0); // Front Side
    mesh.addNormal(1.0, 0.0, 0.0);
    mesh.addNormal(1.0, 0.0, 0.0);
    mesh.addNormal(1.0, 0.0, 0.0);
    mesh.addNormal(1.0, 0.0, 0.0); // Right Side
    mesh.addNormal(0.0, 0.0, -1.0);
    mesh.addNormal(0.0, 0.0, -1.0);
    mesh.addNormal(0.0, 0.0, -1.0);
    mesh.addNormal(0.0, 0.0, -1.0); // Back Side
    mesh.addNormal(-1.0, 0.0, 0.0);
    mesh.addNormal(-1.0, 0.0, 0.0);
    mesh.addNormal(-1.0, 0.0, 0.0);
    mesh.addNormal(-1.0, 0.0, 0.0); // Left Side
    mesh.addNormal(0.0, 1.0, 0.0);
    mesh.addNormal(0.0, 1.0, 0.0);
    mesh.addNormal(0.0, 1.0, 0.0);
    mesh.addNormal(0.0, 1.0, 0.0); // Top Side
    mesh.addNormal(0.0, -1.0, 0.0);
    mesh.addNormal(0.0, -1.0, 0.0);
    mesh.addNormal(0.0, -1.0, 0.0);
    mesh.addNormal(0.0, -1.0, 0.0); // Bottom side
}

void Chunk::render(const std::unique_ptr<Shader> &shader)
{
    GLuint textureID = glGetUniformLocation(shader->getProgramID(), "textureSampler");
    GLuint modelID = glGetUniformLocation(shader->getProgramID(), "model");

    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, tex2.handle);
    // glUniform1i(textureID, 0);

    modelMatrix[3][0] = position.x * CHUNK_SIZE;
    modelMatrix[3][1] = position.y * CHUNK_SIZE;
    modelMatrix[3][2] = position.z * CHUNK_SIZE;

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

    mc::bindVAO(vertexArrayID);
    mc::bindVBO(vertexBuffer);
    mc::vaoEnable(0, 3, GL_FLOAT, 0, 0);

    // mc::bindVBO(uvBuffer);
    // mc::vaoEnable(1, 2, GL_FLOAT, 0, 0);

    mc::bindVBO(normalsBuffer);
    mc::vaoEnable(1, 3, GL_FLOAT, 0, 0);

    unsigned int *NULLptr = 0;
    glDrawElements(
        GL_TRIANGLES,
        mesh.indices.size(),
        GL_UNSIGNED_SHORT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Chunk::setBlock(glm::vec3 position, BlockType bType)
{
    int newIndex = get1DIndexForPosition(position);
    blocks[newIndex] = bType;
}