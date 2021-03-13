#include "renderer.h"

using namespace mc;

Renderer::Renderer()
{
    auto skyboxShader = new Shader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");
    auto regularBlockShader = new Shader("../src/shaders/main.vs", "../src/shaders/main.fs");
    auto waterBlockShader = new Shader("../src/shaders/water.vs", "../src/shaders/water.fs");
    skyboxShader->load();
    regularBlockShader->load();
    waterBlockShader->load();

    shaders[ShaderType::Skybox] = skyboxShader;
    shaders[ShaderType::RegularBlock] = regularBlockShader;
    shaders[ShaderType::WaterBlock] = waterBlockShader;
}

void Renderer::render(Entity *entity, ShaderType shaderType)
{
    switch (shaderType)
    {
    case ShaderType::RegularBlock:
        renderEntityWithRegularBlockShader(entity);
        break;
    case ShaderType::WaterBlock:
        renderEntityWithWaterBlockShader(entity);
        break;
    default:
        break;
    }
}

void Renderer::renderEntityWithWaterBlockShader(Entity *entity)
{
    GLuint programID = shaders[ShaderType::WaterBlock]->getProgramID();
    glUseProgram(programID);

    auto modelMatrix = *entity->getModelMatrix();

    // VS
    GLuint projectionID = glGetUniformLocation(programID, "projection");
    GLuint viewID = glGetUniformLocation(programID, "view");
    GLuint modelID = glGetUniformLocation(programID, "model");
    // FS
    GLuint textureID = glGetUniformLocation(programID, "textureSampler");
    // GLuint lightPosID = glGetUniformLocation(programID, "lightPositionWorldspace");

    // VS
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);
    // FS
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->getTexture()->handle);
    glUniform1i(textureID, 0);
    // glUniform3f(lightPosID, 0, 0, 0);

    GLuint vao = entity->getVAO();
    auto vbos = entity->getVBOs();
    mc::bindVAO(vao);

    int i = 0;
    for (auto const &vbo : vbos)
    {
        if (vbo.type == GL_ARRAY_BUFFER)
        {
            mc::bindVBO(vbo);
            mc::vaoEnable(i, vbo.size, GL_FLOAT, 0, 0);
            i++;
        }
    }

    glDrawElements(
        GL_TRIANGLES,
        entity->getMesh()->indices.size(),
        GL_UNSIGNED_INT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Renderer::renderEntityWithRegularBlockShader(Entity *entity)
{
    GLuint programID = shaders[ShaderType::RegularBlock]->getProgramID();
    glUseProgram(programID);

    auto modelMatrix = *entity->getModelMatrix();

    // VS
    GLuint projectionID = glGetUniformLocation(programID, "projection");
    GLuint viewID = glGetUniformLocation(programID, "view");
    GLuint modelID = glGetUniformLocation(programID, "model");
    // FS
    GLuint textureID = glGetUniformLocation(programID, "textureSampler");
    GLuint lightPosID = glGetUniformLocation(programID, "lightPositionWorldspace");

    // VS
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &projectionMatrix[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &viewMatrix[0][0]);
    glUniformMatrix4fv(modelID, 1, GL_FALSE, &modelMatrix[0][0]);
    // FS
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->getTexture()->handle);
    glUniform1i(textureID, 0);
    glUniform3f(lightPosID, 0, 0, 0);

    GLuint vao = entity->getVAO();
    auto vbos = entity->getVBOs();
    mc::bindVAO(vao);

    int i = 0;
    for (auto const &vbo : vbos)
    {
        if (vbo.type == GL_ARRAY_BUFFER)
        {
            mc::bindVBO(vbo);
            mc::vaoEnable(i, vbo.size, GL_FLOAT, 0, 0);
            i++;
        }
    }

    glDrawElements(
        GL_TRIANGLES,
        entity->getMesh()->indices.size(),
        GL_UNSIGNED_INT,
        (void *)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}