#include "chunk.h"

using namespace mc;

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

                    int blockatlasOffset = blockTextureOffsets[value];

                    float u1 = (double)1 / numTexturesInAtlas * blockatlasOffset;
                    float u2 = ((double)1 / numTexturesInAtlas) * (blockatlasOffset + 1);

                    glm::vec2 uvBottomLeft(u1, 0);
                    glm::vec2 uvBottomRight(u2, 0);
                    glm::vec2 uvTopLeft(u1, 1);
                    glm::vec2 uvTopRight(u2, 1);

                    //Top face
                    if (y == Chunk::CHUNK_SIZE - 1 || getBlock(glm::vec3(x, y + 1, z)) == BlockType::Air)
                    {
                        mesh.indices.push_back(size + 1); // top left
                        mesh.indices.push_back(size);     // bottom left
                        mesh.indices.push_back(size + 2); // bottom right

                        mesh.indices.push_back(size + 1); // top left
                        mesh.indices.push_back(size + 2); // bottom right
                        mesh.indices.push_back(size + 3); // top right

                        mesh.addVertex(nx, py, pz); // front top left
                        mesh.addVertex(nx, py, nz); // back top left
                        mesh.addVertex(px, py, pz); // front top right
                        mesh.addVertex(px, py, nz); // back top right

                        if (value == BlockType::Grass)
                        {
                            float grassU1 = (double)1 / numTexturesInAtlas * (blockatlasOffset + 1);
                            float grassU2 = ((double)1 / numTexturesInAtlas) * (blockatlasOffset + 2);

                            glm::vec2 grassUvBottomLeft(grassU1, 0);
                            glm::vec2 grassUvBottomRight(grassU2, 0);
                            glm::vec2 grassUvTopLeft(grassU1, 1);
                            glm::vec2 grassUvTopRight(grassU2, 1);

                            mesh.addUV(grassUvBottomLeft);
                            mesh.addUV(grassUvBottomRight);
                            mesh.addUV(grassUvTopLeft);
                            mesh.addUV(grassUvTopRight);
                        }
                        else
                        {
                            mesh.addUV(uvBottomLeft);
                            mesh.addUV(uvTopLeft);
                            mesh.addUV(uvBottomRight);
                            mesh.addUV(uvTopRight);
                        }

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

                        mesh.addUV(uvBottomLeft);
                        mesh.addUV(uvTopLeft);
                        mesh.addUV(uvBottomRight);
                        mesh.addUV(uvTopRight);

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

                        mesh.addUV(uvBottomLeft);
                        mesh.addUV(uvTopLeft);
                        mesh.addUV(uvBottomRight);
                        mesh.addUV(uvTopRight);

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

                        mesh.addUV(uvBottomLeft);
                        mesh.addUV(uvTopLeft);
                        mesh.addUV(uvBottomRight);
                        mesh.addUV(uvTopRight);

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

                        mesh.addUV(uvBottomLeft);
                        mesh.addUV(uvTopLeft);
                        mesh.addUV(uvBottomRight);
                        mesh.addUV(uvTopRight);

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

                        mesh.addUV(uvBottomLeft);
                        mesh.addUV(uvTopLeft);
                        mesh.addUV(uvBottomRight);
                        mesh.addUV(uvTopRight);

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
    glBindTexture(GL_TEXTURE_2D, blockatlasTexture.handle);
    glUniform1i(textureID, 0);

    modelMatrix[3][0] = position.x * CHUNK_SIZE;
    // modelMatrix[3][1] = position.y * CHUNK_SIZE;
    modelMatrix[3][2] = position.y * CHUNK_SIZE;

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