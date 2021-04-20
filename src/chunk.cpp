#include "chunk.h"

using namespace mc;

void Chunk::createMesh()
{
    for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
        {
            for (int y = 0; y < Chunk::CHUNK_HEIGHT; y++)
            {

                BlockType blockType = getBlock(glm::vec3(x, y, z));

                if (blockType == BlockType::Air)
                {
                    continue;
                }

                if (blockType == BlockType::Water)
                    addCubeToMesh(glm::vec3(x, y, z), blockType, waterMesh, &waterMeshSize);
                else
                    addCubeToMesh(glm::vec3(x, y, z), blockType, blockMesh, &blockMeshSize);
            }
        }
    }

    glGenVertexArrays(1, &blockMeshVertexArrayID);
    glBindVertexArray(blockMeshVertexArrayID);

    glGenBuffers(1, &blockMeshVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh->vertices[0]) * blockMesh->vertices.size(), &blockMesh->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &blockMeshUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh->uvCoordinates[0]) * blockMesh->uvCoordinates.size(), &blockMesh->uvCoordinates[0], GL_STATIC_DRAW);

    glGenBuffers(1, &blockMeshIndicesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshIndicesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh->indices[0]) * blockMesh->indices.size(), &blockMesh->indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &blockMeshNormalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blockMesh->normals[0]) * blockMesh->normals.size(), &blockMesh->normals[0], GL_STATIC_DRAW);

    glGenVertexArrays(1, &waterMeshVertexArrayID);
    glBindVertexArray(waterMeshVertexArrayID);

    glGenBuffers(1, &waterMeshVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterMesh->vertices[0]) * waterMesh->vertices.size(), &waterMesh->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &waterMeshUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterMesh->uvCoordinates[0]) * waterMesh->uvCoordinates.size(), &waterMesh->uvCoordinates[0], GL_STATIC_DRAW);

    glGenBuffers(1, &waterMeshIndicesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshIndicesBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterMesh->indices[0]) * waterMesh->indices.size(), &waterMesh->indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &waterMeshNormalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(waterMesh->normals[0]) * waterMesh->normals.size(), &waterMesh->normals[0], GL_STATIC_DRAW);
}

void Chunk::addCubeToMesh(glm::vec3 cubePos, BlockType type, Mesh *mesh, int *meshSize)
{
    //Positive
    float px = 0.5f + cubePos.x;
    float py = 0.5f + cubePos.y;
    float pz = 0.5f + cubePos.z;

    //Negative
    float nx = cubePos.x - 0.5f;
    float ny = cubePos.y - 0.5f;
    float nz = cubePos.z - 0.5f;

    int blockatlasOffset = blockTextureOffsets[type];

    float u1 = (double)1 / numTexturesInAtlas * blockatlasOffset;
    float u2 = ((double)1 / numTexturesInAtlas) * (blockatlasOffset + 1);

    glm::vec2 uvBottomLeft(u1, 0);
    glm::vec2 uvBottomRight(u2, 0);
    glm::vec2 uvTopLeft(u1, 1);
    glm::vec2 uvTopRight(u2, 1);

    int cubeWorldX = position.x * CHUNK_SIZE + cubePos.x;
    int cubeWorldZ = position.y * CHUNK_SIZE + cubePos.z;

    BlockType topBlockType = getBlock(glm::vec3(cubePos.x, cubePos.y + 1, cubePos.z));
    BlockType bottomBlockType = getBlock(glm::vec3(cubePos.x, cubePos.y - 1, cubePos.z));

    BlockType leftBlockType = getBlock(glm::vec3(cubePos.x - 1, cubePos.y, cubePos.z));
    if (cubePos.x == 0)
    {
        Chunk *neighbourChunk = world->getChunk(glm::ivec2(position.x - 1, position.y));
        if (neighbourChunk)
        {
            leftBlockType = neighbourChunk->getBlock(glm::ivec3(CHUNK_SIZE - 1, cubePos.y, cubePos.z));
        }
    }
    BlockType rightBlockType = getBlock(glm::vec3(cubePos.x + 1, cubePos.y, cubePos.z));
    if (cubePos.x == CHUNK_SIZE - 1)
    {
        Chunk *neighbourChunk = world->getChunk(glm::ivec2(position.x + 1, position.y));
        if (neighbourChunk)
        {
            rightBlockType = neighbourChunk->getBlock(glm::ivec3(0, cubePos.y, cubePos.z));
        }
    }
    BlockType frontBlockType = getBlock(glm::vec3(cubePos.x, cubePos.y, cubePos.z + 1));
    if (cubePos.z == CHUNK_SIZE - 1)
    {
        Chunk *neighbourChunk = world->getChunk(glm::ivec2(position.x, position.y + 1));
        if (neighbourChunk)
        {
            frontBlockType = neighbourChunk->getBlock(glm::ivec3(0, cubePos.y, cubePos.z));
        }
    }
    BlockType backBlockType = getBlock(glm::vec3(cubePos.x, cubePos.y, cubePos.z - 1));
    if (cubePos.z == 0)
    {
        Chunk *neighbourChunk = world->getChunk(glm::ivec2(position.x, position.y - 1));
        if (neighbourChunk)
        {
            backBlockType = neighbourChunk->getBlock(glm::ivec3(CHUNK_SIZE - 1, cubePos.y, cubePos.z));
        }
    }

    if (type == BlockType::Water)
    {
        //! Special case
        if (topBlockType == BlockType::Air)
        {
            mesh->indices.push_back(*meshSize + 1); // top left
            mesh->indices.push_back(*meshSize);     // bottom left
            mesh->indices.push_back(*meshSize + 2); // bottom right

            mesh->indices.push_back(*meshSize + 1); // top left
            mesh->indices.push_back(*meshSize + 2); // bottom right
            mesh->indices.push_back(*meshSize + 3); // top right

            mesh->addVertex(nx, py, pz); // front top left
            mesh->addVertex(nx, py, nz); // back top left
            mesh->addVertex(px, py, pz); // front top right
            mesh->addVertex(px, py, nz); // back top right

            mesh->addUV(uvBottomLeft);
            mesh->addUV(uvTopLeft);
            mesh->addUV(uvBottomRight);
            mesh->addUV(uvTopRight);

            mesh->addNormal(0.0, 1.0, 0.0);
            mesh->addNormal(0.0, 1.0, 0.0);
            mesh->addNormal(0.0, 1.0, 0.0);
            mesh->addNormal(0.0, 1.0, 0.0); // Top Side

            *meshSize += 4;
        }
        return;
    }

    // Top face
    if (cubePos.y == Chunk::CHUNK_HEIGHT - 1 || topBlockType == BlockType::Air || topBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize + 1); // top left
        mesh->indices.push_back(*meshSize);     // bottom left
        mesh->indices.push_back(*meshSize + 2); // bottom right

        mesh->indices.push_back(*meshSize + 1); // top left
        mesh->indices.push_back(*meshSize + 2); // bottom right
        mesh->indices.push_back(*meshSize + 3); // top right

        mesh->addVertex(nx, py, pz); // front top left
        mesh->addVertex(nx, py, nz); // back top left
        mesh->addVertex(px, py, pz); // front top right
        mesh->addVertex(px, py, nz); // back top right

        if (type == BlockType::Grass)
        {
            float grassU1 = (double)1 / numTexturesInAtlas * (blockatlasOffset + 1);
            float grassU2 = ((double)1 / numTexturesInAtlas) * (blockatlasOffset + 2);

            glm::vec2 grassUvBottomLeft(grassU1, 0);
            glm::vec2 grassUvBottomRight(grassU2, 0);
            glm::vec2 grassUvTopLeft(grassU1, 1);
            glm::vec2 grassUvTopRight(grassU2, 1);

            mesh->addUV(grassUvBottomLeft);
            mesh->addUV(grassUvBottomRight);
            mesh->addUV(grassUvTopLeft);
            mesh->addUV(grassUvTopRight);
        }
        else
        {
            mesh->addUV(uvBottomLeft);
            mesh->addUV(uvTopLeft);
            mesh->addUV(uvBottomRight);
            mesh->addUV(uvTopRight);
        }

        mesh->addNormal(0.0, 1.0, 0.0);
        mesh->addNormal(0.0, 1.0, 0.0);
        mesh->addNormal(0.0, 1.0, 0.0);
        mesh->addNormal(0.0, 1.0, 0.0); // Top Side

        *meshSize += 4;
    }

    //Bottom face
    if ((cubePos.y == 0 && type != BlockType::Water) || bottomBlockType == BlockType::Air || bottomBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize + 1);
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 2);

        mesh->addVertex(px, ny, pz);
        mesh->addVertex(px, ny, nz);
        mesh->addVertex(nx, ny, pz);
        mesh->addVertex(nx, ny, nz);

        mesh->addUV(uvBottomLeft);
        mesh->addUV(uvTopLeft);
        mesh->addUV(uvBottomRight);
        mesh->addUV(uvTopRight);

        mesh->addNormal(0.0, -1.0, 0.0);
        mesh->addNormal(0.0, -1.0, 0.0);
        mesh->addNormal(0.0, -1.0, 0.0);
        mesh->addNormal(0.0, -1.0, 0.0); // Bottom side
        *meshSize += 4;
    }

    //Front face
    if ((cubePos.z == Chunk::CHUNK_SIZE - 1 && type != BlockType::Water) || frontBlockType == BlockType::Air || frontBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize + 1);

        mesh->addVertex(nx, ny, pz);
        mesh->addVertex(nx, py, pz);
        mesh->addVertex(px, ny, pz);
        mesh->addVertex(px, py, pz);

        mesh->addUV(uvBottomLeft);
        mesh->addUV(uvTopLeft);
        mesh->addUV(uvBottomRight);
        mesh->addUV(uvTopRight);

        mesh->addNormal(0.0, 0.0, 1.0);
        mesh->addNormal(0.0, 0.0, 1.0);
        mesh->addNormal(0.0, 0.0, 1.0);
        mesh->addNormal(0.0, 0.0, 1.0); // Front Side

        *meshSize += 4;
    }

    //Back face
    if ((cubePos.z == 0 && type != BlockType::Water) || backBlockType == BlockType::Air || backBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize + 1);
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 1);
        mesh->indices.push_back(*meshSize);

        mesh->addVertex(px, ny, nz);
        mesh->addVertex(px, py, nz);
        mesh->addVertex(nx, ny, nz);
        mesh->addVertex(nx, py, nz);

        mesh->addUV(uvBottomLeft);
        mesh->addUV(uvTopLeft);
        mesh->addUV(uvBottomRight);
        mesh->addUV(uvTopRight);

        mesh->addNormal(0.0, 0.0, -1.0);
        mesh->addNormal(0.0, 0.0, -1.0);
        mesh->addNormal(0.0, 0.0, -1.0);
        mesh->addNormal(0.0, 0.0, -1.0); // Back Side

        *meshSize += 4;
    }

    //Right face
    if ((cubePos.x == Chunk::CHUNK_SIZE - 1 && type != BlockType::Water) || rightBlockType == BlockType::Air || rightBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize + 1);
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 1);
        mesh->indices.push_back(*meshSize);

        mesh->addVertex(px, ny, pz);
        mesh->addVertex(px, py, pz);
        mesh->addVertex(px, ny, nz);
        mesh->addVertex(px, py, nz);

        mesh->addUV(uvBottomLeft);
        mesh->addUV(uvTopLeft);
        mesh->addUV(uvBottomRight);
        mesh->addUV(uvTopRight);

        mesh->addNormal(1.0, 0.0, 0.0);
        mesh->addNormal(1.0, 0.0, 0.0);
        mesh->addNormal(1.0, 0.0, 0.0);
        mesh->addNormal(1.0, 0.0, 0.0); // Right Side

        *meshSize += 4;
    }

    //Left face
    if ((cubePos.x == 0 && type != BlockType::Water) || leftBlockType == BlockType::Air || leftBlockType == BlockType::Water)
    {
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 2);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize);
        mesh->indices.push_back(*meshSize + 3);
        mesh->indices.push_back(*meshSize + 1);

        mesh->addVertex(nx, ny, nz);
        mesh->addVertex(nx, py, nz);
        mesh->addVertex(nx, ny, pz);
        mesh->addVertex(nx, py, pz);

        mesh->addUV(uvBottomLeft);
        mesh->addUV(uvTopLeft);
        mesh->addUV(uvBottomRight);
        mesh->addUV(uvTopRight);

        mesh->addNormal(-1.0, 0.0, 0.0);
        mesh->addNormal(-1.0, 0.0, 0.0);
        mesh->addNormal(-1.0, 0.0, 0.0);
        mesh->addNormal(-1.0, 0.0, 0.0); // Left Side

        *meshSize += 4;
    }
}

void Chunk::renderBlockMesh(const std::unique_ptr<Shader> &shader)
{
    modelMatrix[3][0] = position.x * CHUNK_SIZE;
    modelMatrix[3][2] = position.y * CHUNK_SIZE;

    shader->use();

    shader->uniformMat4f("model", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    shader->uniform1i("textureSampler", 0);
    shader->uniform3f("lightPositionWorldspace", 0, 0, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshUvBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, blockMeshNormalsBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, blockMeshIndicesBuffer);

    glDrawElements(
        GL_TRIANGLES,
        blockMesh->indices.size(),
        GL_UNSIGNED_INT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Chunk::renderWaterMesh(const std::unique_ptr<Shader> &shader)
{
    modelMatrix[3][0] = position.x * CHUNK_SIZE;
    modelMatrix[3][2] = position.y * CHUNK_SIZE;

    shader->use();

    shader->uniformMat4f("model", modelMatrix);
    glActiveTexture(GL_TEXTURE0);
    shader->uniform1i("textureSampler", 0);
    shader->uniform3f("lightPositionWorldspace", 0, 0, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshUvBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, waterMeshNormalsBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, waterMeshIndicesBuffer);

    glDrawElements(
        GL_TRIANGLES,
        waterMesh->indices.size(),
        GL_UNSIGNED_INT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}