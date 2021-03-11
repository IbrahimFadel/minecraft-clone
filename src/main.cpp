#include <stdio.h>
#include <iostream>
using std::cout;
#include <memory>
#include <vector>
#include <cmath>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "shader.h"
#include "rendering/vao.h"

#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"

#include "camera.h"
#include "terrain/block.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "terrain/chunk.h"

#include "terrain/world.h"

#include "player.h"

void initGLFW()
{
    glewExperimental = true;
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
}

void initGLEW(GLFWwindow *window)
{
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true;        // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(1);
    }
}

void GLAPIENTRY
MessageCallback(GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar *message,
                const void *userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

int main()
{
    initGLFW();

    auto window = std::make_unique<mc::Window>(1024, 768, "Minecraft");
    auto glfwWindow = window->getGLFWWindow();

    initGLEW(glfwWindow);
    glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE);

    auto mirrorShader = std::make_unique<mc::Shader>("../src/shaders/mirror.vs", "../src/shaders/mirror.fs");
    mirrorShader->load();

    auto skyboxShader = std::make_unique<mc::Shader>("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");
    skyboxShader->load();

    std::vector<std::string> faces =
        {
            "../assets/right.jpg",
            "../assets/left.jpg",
            "../assets/top.jpg",
            "../assets/bottom.jpg",
            "../assets/front.jpg",
            "../assets/back.jpg"};

    GLuint skyboxTexture = loadCubemap(faces);

    float skyboxVertices[] = {
        // positions
        -1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // GLuint skyboxVAO = mc::createVAO();
    // mc::VBO skyboxVBO = mc::createVBO(GL_ARRAY_BUFFER);
    // mc::vboBuffer(skyboxVBO, sizeof(skyboxVertices), &skyboxVertices[0]);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    auto shader = std::make_unique<mc::Shader>("../src/shaders/main.vs", "../src/shaders/main.fs");
    shader->load();
    GLuint programID = shader->getProgramID();

    GLuint projectionID = glGetUniformLocation(mirrorShader->getProgramID(), "projection");
    GLuint viewID = glGetUniformLocation(mirrorShader->getProgramID(), "view");
    GLuint lightPositionWorldspaceID = glGetUniformLocation(mirrorShader->getProgramID(), "lightPositionWorldspace");

    glm::vec3 lightPos = glm::vec3(0, 40, 0);

    mc::Texture tex = mc::createTextureFromPath("../assets/stone.jpg");

    auto world = std::make_unique<mc::World>();
    // world.generateHeightmap();
    // world.generateChunk(glm::vec3(0, 0, 0));
    // world.generateChunk(glm::vec3(1, 0, 0));
    // world.generateChunk(glm::vec3(0, 0, 1));
    // world.generateChunk(glm::vec3(1, 0, 1));

    // mc::Chunk *chunk = new mc::Chunk();
    // chunk->setPosition(vec3(0, 0, 0));
    // chunk->createMesh();
    // chunk->setWorld()

    auto player = std::make_unique<mc::Player>(glm::vec3(0, world->getBlockHeightAtWorldPosition(glm::ivec2(0, 0)) + mc::Player::playerHeight, 0), world, window);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEBUG_OUTPUT);
    // glDebugMessageCallback(MessageCallback, 0);

    bool wireframe = false;
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

    while (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(glfwWindow) == 0)
    {
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);

        player->handleMovement();
        player->updateCameraMatrices();

        glUniformMatrix4fv(projectionID, 1, GL_FALSE, &player->getCamera()->getProjection()[0][0]);
        glUniformMatrix4fv(viewID, 1, GL_FALSE, &player->getCamera()->getView()[0][0]);
        glUniform3f(lightPositionWorldspaceID, lightPos.x, lightPos.y, lightPos.z);

        // glUseProgram(mirrorShader->getProgramID());

        // GLuint projectionID = glGetUniformLocation(programID, "projection");
        // GLuint viewID = glGetUniformLocation(programID, "view");

        // glUniformMatrix4fv(projectionID, 1, GL_FALSE, &camera->getProjection()[0][0]);
        // glUniformMatrix4fv(viewID, 1, GL_FALSE, &camera->getView()[0][0]);
        // glUniform3f(glGetUniformLocation(mirrorShader->getProgramID(), "cameraPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

        glm::vec3 pos = player->getCamera()->getPosition();

        float cx = pos.x / 16;
        cx = cx < 0 ? ceil(abs(cx)) * -1 : floor(cx);
        float cz = pos.z / 16;
        cz = cz < 0 ? ceil(abs(cz)) * -1 : floor(cz);

        glm::ivec2 chunk(cx, cz);

        glm::ivec2 front(cx, cz + 1);
        glm::ivec2 right(cx + 1, cz);
        glm::ivec2 back(cx, cz - 1);
        glm::ivec2 left(cx - 1, cz);

        glm::ivec2 frontRight(cx + 1, cz + 1);
        glm::ivec2 frontLeft(cx - 1, cz + 1);
        glm::ivec2 backRight(cx + 1, cz - 1);
        glm::ivec2 backLeft(cx - 1, cz - 1);

        if (!world->getChunk(chunk))
        {
            world->generateChunk(chunk);
        }
        if (!world->getChunk(front))
        {
            world->generateChunk(front);
        }
        if (!world->getChunk(right))
        {
            world->generateChunk(right);
        }
        if (!world->getChunk(back))
        {
            world->generateChunk(back);
        }
        if (!world->getChunk(left))
        {
            world->generateChunk(left);
        }
        if (!world->getChunk(frontRight))
        {
            world->generateChunk(frontRight);
        }
        if (!world->getChunk(frontLeft))
        {
            world->generateChunk(frontLeft);
        }
        if (!world->getChunk(backRight))
        {
            world->generateChunk(backRight);
        }
        if (!world->getChunk(backLeft))
        {
            world->generateChunk(backLeft);
        }

        world->render(shader);
        // chunk->render(shader);

        glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
        glUseProgram(skyboxShader->getProgramID());
        auto view = glm::mat4(glm::mat3(player->getCamera()->getView())); // remove translation from the view matrix
        GLuint skyboxProjID = glGetUniformLocation(skyboxShader->getProgramID(), "projection");
        GLuint skyboxViewID = glGetUniformLocation(skyboxShader->getProgramID(), "view");
        glUniformMatrix4fv(skyboxProjID, 1, GL_FALSE, &player->getCamera()->getProjection()[0][0]);
        glUniformMatrix4fv(skyboxViewID, 1, GL_FALSE, &view[0][0]);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        // glDepthMask(GL_FALSE);
        // glDepthFunc(GL_LEQUAL);
        // glUseProgram(skyboxShader->getProgramID());

        // GLuint skyboxProjID = glGetUniformLocation(skyboxShader->getProgramID(), "projection");
        // GLuint skyboxViewID = glGetUniformLocation(skyboxShader->getProgramID(), "view");

        // glUniformMatrix4fv(skyboxProjID, 1, GL_FALSE, &camera->getProjection()[0][0]);
        // auto view = glm::mat4(glm::mat3(camera->getView()));
        // glUniformMatrix4fv(skyboxViewID, 1, GL_FALSE, &view[0][0]);

        // glBindVertexArray(skyboxVAO);
        // glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

        // mc::bindVAO(skyboxVAO);
        // mc::bindVBO(skyboxVBO);
        // mc::vaoEnable(0, 3, GL_FLOAT, 0, 0);

        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDepthMask(GL_TRUE);

        // glm::vec3 pos = camera->getPosition();

        // float cx = pos.x / 16;
        // cx = cx < 0 ? ceil(abs(cx)) * -1 : floor(cx);
        // float cz = pos.z / 16;
        // cz = cz < 0 ? ceil(abs(cz)) * -1 : floor(cz);

        // glm::ivec3 chunk(cx, 0, cz);

        // glm::ivec3 front(cx, 0, cz + 1);
        // glm::ivec3 right(cx + 1, 0, cz);
        // glm::ivec3 back(cx, 0, cz - 1);
        // glm::ivec3 left(cx - 1, 0, cz);

        // glm::ivec3 frontRight(cx + 1, 0, cz + 1);
        // glm::ivec3 frontLeft(cx - 1, 0, cz + 1);
        // glm::ivec3 backRight(cx + 1, 0, cz - 1);
        // glm::ivec3 backLeft(cx - 1, 0, cz - 1);

        // if (!world.getChunk(chunk))
        // {
        //     world.generateChunk(chunk);
        // }
        // if (!world.getChunk(front))
        // {
        //     world.generateChunk(front);
        // }
        // if (!world.getChunk(right))
        // {
        //     world.generateChunk(right);
        // }
        // if (!world.getChunk(back))
        // {
        //     world.generateChunk(back);
        // }
        // if (!world.getChunk(left))
        // {
        //     world.generateChunk(left);
        // }
        // if (!world.getChunk(frontRight))
        // {
        //     world.generateChunk(frontRight);
        // }
        // if (!world.getChunk(frontLeft))
        // {
        //     world.generateChunk(frontLeft);
        // }
        // if (!world.getChunk(backRight))
        // {
        //     world.generateChunk(backRight);
        // }
        // if (!world.getChunk(backLeft))
        // {
        //     world.generateChunk(backLeft);
        // }

        // world.render(shader);

        // Swap buffers
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}