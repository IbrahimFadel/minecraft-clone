#include "block.h"

// mc::Block::Block(BlockType type, glm::vec3 position) : type(type), position(position)
mc::Block::Block()
{
    type = BlockType::Air;
    fillBlockTextureMap();

    // vertexArrayID = mc::createVAO();
    // mc::bindVAO(vertexArrayID);

    // vertexBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    // mc::bindVBO(vertexBuffer);
    // mc::vboBuffer(vertexBuffer, sizeof(mc::blockVertexData), &mc::blockVertexData[0]);

    // uvBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    // mc::bindVBO(uvBuffer);
    // mc::vboBuffer(uvBuffer, sizeof(mc::blockUVData), &mc::blockUVData[0]);

    // indicesBuffer = mc::createVBO(GL_ELEMENT_ARRAY_BUFFER);
    // mc::bindVBO(indicesBuffer);
    // mc::vboBuffer(indicesBuffer, sizeof(mc::blockIndicesData), &mc::blockIndicesData[0]);

    // normalsBuffer = mc::createVBO(GL_ARRAY_BUFFER);
    // mc::bindVBO(normalsBuffer);
    // mc::vboBuffer(normalsBuffer, sizeof(mc::blockNormalsData), &mc::blockNormalsData[0]);
}

void mc::Block::fillBlockTextureMap()
{
    Texture EndStoneTexture = mc::createTextureFromPath("../assets/stone.jpg");
    // Texture EndStoneTexture = mc::createTextureFromPath("../assets/endstone.png");
    blockTextures[BlockType::EndStone] = EndStoneTexture;
}

// void mc::Block::render(const std::unique_ptr<Shader> &shader)
// {
//     GLuint textureID = glGetUniformLocation(shader->getProgramID(), "textureSampler");
//     GLuint modelID = glGetUniformLocation(shader->getProgramID(), "model");

//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_2D, blockTextures[type].handle);
//     glUniform1i(textureID, 0);

//     modelMatrix[3][0] = position.x;
//     modelMatrix[3][1] = position.y;
//     modelMatrix[3][2] = position.z;

//     glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);

//     mc::bindVAO(vertexArrayID);
//     mc::bindVBO(vertexBuffer);
//     mc::vaoEnable(0, 3, GL_FLOAT, 0, 0);

//     mc::bindVBO(uvBuffer);
//     mc::vaoEnable(1, 2, GL_FLOAT, 0, 0);

//     mc::bindVBO(normalsBuffer);
//     mc::vaoEnable(2, 3, GL_FLOAT, 0, 0);

//     glDrawElements(
//         GL_TRIANGLES,
//         sizeof(mc::blockIndicesData) / sizeof(mc::blockIndicesData[0]),
//         GL_UNSIGNED_SHORT,
//         (void *)0);

//     glDisableVertexAttribArray(0);
//     glDisableVertexAttribArray(1);
//     glDisableVertexAttribArray(2);
// }