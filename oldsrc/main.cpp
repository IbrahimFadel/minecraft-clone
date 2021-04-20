#include <glBoilerplate.h>
#include "window.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <cubemap.h>
#include <quad.h>

#include <memory>

int main()
{
    initGLFW();
    mc::Window *window = new mc::Window(1024, 720, "IbCraft");
    GLFWwindow *glfwWindow = window->getGLFWWindow();
    initGLEW(glfwWindow);

    auto skyboxShader = std::make_unique<mc::Shader>();
    skyboxShader->initVertexFragmentShader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

    std::vector<std::string> faces =
        {
            "../assets/right.jpg",
            "../assets/left.jpg",
            "../assets/top.jpg",
            "../assets/bottom.jpg",
            "../assets/front.jpg",
            "../assets/back.jpg"};
    GLuint cubemapTexture = loadCubemap(faces);
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    while (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(glfwWindow) == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        skyboxShader->use();

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}

// unsigned int loadCubemap(vector<std::string> faces)
// {
//     unsigned int textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

//     int width, height, nrChannels;
//     for (unsigned int i = 0; i < faces.size(); i++)
//     {
//         unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//         if (data)
//         {
//             glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//                          0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//             stbi_image_free(data);
//         }
//         else
//         {
//             std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
//             stbi_image_free(data);
//         }
//     }
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//     return textureID;
// }

// void updateWorld(const std::unique_ptr<mc::World> &world, int cx, int cz)
// {
//     glm::ivec2 chunk(cx, cz);

//     glm::ivec2 front(cx, cz + 1);
//     glm::ivec2 right(cx + 1, cz);
//     glm::ivec2 back(cx, cz - 1);
//     glm::ivec2 left(cx - 1, cz);

//     glm::ivec2 frontRight(cx + 1, cz + 1);
//     glm::ivec2 frontLeft(cx - 1, cz + 1);
//     glm::ivec2 backRight(cx + 1, cz - 1);
//     glm::ivec2 backLeft(cx - 1, cz - 1);

//     if (!world->getChunk(chunk))
//     {
//         world->generateChunk(chunk);
//     }
//     if (!world->getChunk(front))
//     {
//         world->generateChunk(front);
//     }
//     if (!world->getChunk(right))
//     {
//         world->generateChunk(right);
//     }
//     if (!world->getChunk(back))
//     {
//         world->generateChunk(back);
//     }
//     if (!world->getChunk(left))
//     {
//         world->generateChunk(left);
//     }
//     if (!world->getChunk(frontRight))
//     {
//         world->generateChunk(frontRight);
//     }
//     if (!world->getChunk(frontLeft))
//     {
//         world->generateChunk(frontLeft);
//     }
//     if (!world->getChunk(backRight))
//     {
//         world->generateChunk(backRight);
//     }
//     if (!world->getChunk(backLeft))
//     {
//         world->generateChunk(backLeft);
//     }
// }

// int main()
// {
// initGLFW();

// auto window = std::make_unique<mc::Window>(1024, 768, "Minecraft");
// auto glfwWindow = window->getGLFWWindow();

// initGLEW(glfwWindow);
// glfwSetInputMode(glfwWindow, GLFW_STICKY_KEYS, GL_TRUE);

// auto mirrorShader = std::make_unique<mc::Shader>("../src/shaders/mirror.vs", "../src/shaders/mirror.fs");
// mirrorShader->load();

// auto skyboxShader = std::make_unique<mc::Shader>("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");
// skyboxShader->load();

// auto waterShader = std::make_unique<mc::Shader>("../src/shaders/water.vs", "../src/shaders.water.fs");
// waterShader->load();

// std::vector<std::string> faces =
//     {
//         "../assets/right.jpg",
//         "../assets/left.jpg",
//         "../assets/top.jpg",
//         "../assets/bottom.jpg",
//         "../assets/front.jpg",
//         "../assets/back.jpg"};

// GLuint skyboxTexture = loadCubemap(faces);

// float skyboxVertices[] = {
//     // positions
//     -1.0f, 1.0f, -1.0f,
//     -1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, 1.0f, -1.0f,
//     -1.0f, 1.0f, -1.0f,

//     -1.0f, -1.0f, 1.0f,
//     -1.0f, -1.0f, -1.0f,
//     -1.0f, 1.0f, -1.0f,
//     -1.0f, 1.0f, -1.0f,
//     -1.0f, 1.0f, 1.0f,
//     -1.0f, -1.0f, 1.0f,

//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, 1.0f,
//     1.0f, 1.0f, 1.0f,
//     1.0f, 1.0f, 1.0f,
//     1.0f, 1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,

//     -1.0f, -1.0f, 1.0f,
//     -1.0f, 1.0f, 1.0f,
//     1.0f, 1.0f, 1.0f,
//     1.0f, 1.0f, 1.0f,
//     1.0f, -1.0f, 1.0f,
//     -1.0f, -1.0f, 1.0f,

//     -1.0f, 1.0f, -1.0f,
//     1.0f, 1.0f, -1.0f,
//     1.0f, 1.0f, 1.0f,
//     1.0f, 1.0f, 1.0f,
//     -1.0f, 1.0f, 1.0f,
//     -1.0f, 1.0f, -1.0f,

//     -1.0f, -1.0f, -1.0f,
//     -1.0f, -1.0f, 1.0f,
//     1.0f, -1.0f, -1.0f,
//     1.0f, -1.0f, -1.0f,
//     -1.0f, -1.0f, 1.0f,
//     1.0f, -1.0f, 1.0f};

// unsigned int skyboxVAO, skyboxVBO;
// glGenVertexArrays(1, &skyboxVAO);
// glGenBuffers(1, &skyboxVBO);
// glBindVertexArray(skyboxVAO);
// glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
// glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
// glEnableVertexAttribArray(0);
// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

// // GLuint skyboxVAO = mc::createVAO();
// // mc::VBO skyboxVBO = mc::createVBO(GL_ARRAY_BUFFER);
// // mc::vboBuffer(skyboxVBO, sizeof(skyboxVertices), &skyboxVertices[0]);
// // glEnableVertexAttribArray(0);
// // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

// auto shader = std::make_unique<mc::Shader>("../src/shaders/main.vs", "../src/shaders/main.fs");
// shader->load();
// GLuint programID = shader->getProgramID();

// GLuint projectionID = glGetUniformLocation(mirrorShader->getProgramID(), "projection");
// GLuint viewID = glGetUniformLocation(mirrorShader->getProgramID(), "view");
// GLuint lightPositionWorldspaceID = glGetUniformLocation(mirrorShader->getProgramID(), "lightPositionWorldspace");

// glm::vec3 lightPos = glm::vec3(0, 40, 0);

// mc::Texture tex = mc::createTextureFromPath("../assets/stone.jpg");

// auto world = std::make_unique<mc::World>();
// auto player = std::make_unique<mc::Player>(glm::vec3(0, world->getBlockHeightAtWorldPosition(glm::ivec2(0, 0)) + mc::Player::playerHeight, 0), world, window);

// glEnable(GL_DEPTH_TEST);
// glDepthFunc(GL_LESS);
// // glEnable(GL_CULL_FACE);
// // glCullFace(GL_BACK);
// glEnable(GL_BLEND);
// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// glEnable(GL_DEBUG_OUTPUT);
// // glDebugMessageCallback(MessageCallback, 0);

// auto renderer = new mc::Renderer();

// GLuint fbo = mc::createFBO();
// mc::bindFBO(fbo);
// GLuint renderedTexture;
// glGenTextures(1, &renderedTexture);

// glBindTexture(GL_TEXTURE_2D, renderedTexture);

// // Give an empty image to OpenGL ( the last "0" )
// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

// // Poor filtering. Needed !
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// GLuint depthrenderbuffer;
// glGenRenderbuffers(1, &depthrenderbuffer);
// glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
// glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
// glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

// // Set "renderedTexture" as our colour attachement #0
// glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

// // Set the list of draw buffers.
// GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
// glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

// bool wireframe = false;
// glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);

// while (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
//        glfwWindowShouldClose(glfwWindow) == 0)
// {
//     player->handleMovement();
//     player->updateCameraMatrices();

//     glBindFramebuffer(GL_FRAMEBUFFER, fbo);
//     glViewport(0, 0, 1024, 768);

//     glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     renderer->setProjectionMatrix(player->getCamera()->getProjection());
//     renderer->setViewMatrix(player->getCamera()->getView());

//     glm::vec3 pos = player->getCamera()->getPosition();

//     float cx = pos.x / 16;
//     cx = cx < 0 ? ceil(abs(cx)) * -1 : floor(cx);
//     float cz = pos.z / 16;
//     cz = cz < 0 ? ceil(abs(cz)) * -1 : floor(cz);

//     updateWorld(world, cx, cz);

//     // world->render(renderer);
//     for (auto const &[position, chunk] : world->getChunks())
//     {
//         chunk->renderBlockMesh(renderer);
//     }

//     glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
//     glUseProgram(skyboxShader->getProgramID());
//     auto view = glm::mat4(glm::mat3(player->getCamera()->getView())); // remove translation from the view matrix
//     GLuint skyboxProjID = glGetUniformLocation(skyboxShader->getProgramID(), "projection");
//     GLuint skyboxViewID = glGetUniformLocation(skyboxShader->getProgramID(), "view");
//     glUniformMatrix4fv(skyboxProjID, 1, GL_FALSE, &player->getCamera()->getProjection()[0][0]);
//     glUniformMatrix4fv(skyboxViewID, 1, GL_FALSE, &view[0][0]);
//     // skybox cube
//     glBindVertexArray(skyboxVAO);
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
//     glDrawArrays(GL_TRIANGLES, 0, 36);
//     glBindVertexArray(0);
//     glDepthFunc(GL_LESS); // set depth function back to default

//     mc::bindDefaultFBO();

//     glEnable(GL_DEPTH_TEST);
//     glDepthFunc(GL_LESS);
//     glEnable(GL_CULL_FACE);
//     glCullFace(GL_BACK);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//     glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content
//     glUseProgram(skyboxShader->getProgramID());
//     skyboxProjID = glGetUniformLocation(skyboxShader->getProgramID(), "projection");
//     skyboxViewID = glGetUniformLocation(skyboxShader->getProgramID(), "view");
//     glUniformMatrix4fv(skyboxProjID, 1, GL_FALSE, &player->getCamera()->getProjection()[0][0]);
//     glUniformMatrix4fv(skyboxViewID, 1, GL_FALSE, &view[0][0]);
//     // skybox cube
//     glBindVertexArray(skyboxVAO);
//     glActiveTexture(GL_TEXTURE0);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
//     glDrawArrays(GL_TRIANGLES, 0, 36);
//     glBindVertexArray(0);
//     glDepthFunc(GL_LESS); // set depth function back to default

//     // ? I feel like there must be some way to avoid this ugliness... but maybe not. Transparency is annoying
//     for (auto const &[position, chunk] : world->getChunks())
//     {
//         chunk->renderBlockMesh(renderer);
//     }
//     for (auto const &[position, chunk] : world->getChunks())
//     {
//         chunk->renderWaterMesh(renderer, skyboxTexture, player->getCamera()->getPosition());
//     }

//     // Swap buffers
//     glfwSwapBuffers(glfwWindow);
//     glfwPollEvents();
// }

// return 0;
// }