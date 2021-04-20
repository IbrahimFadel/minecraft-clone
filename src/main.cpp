#define STB_IMAGE_IMPLEMENTATION
#include <glBoilerplate.h>
#include "window.h"
#include "shader.h"
#include "texture.h"
#include <quad.h>
#include "world.h"
#include "camera.h"

#include <memory>

int main()
{
    initGLFW();
    auto window = std::make_unique<mc::Window>(1024, 720, "IbCraft");
    GLFWwindow *glfwWindow = window->getGLFWWindow();
    initGLEW(glfwWindow);

    auto skyboxShader = std::make_unique<mc::Shader>();
    skyboxShader->initVertexFragmentShader("../src/shaders/skybox.vs", "../src/shaders/skybox.fs");

    auto blockShader = std::make_unique<mc::Shader>();
    blockShader->initVertexFragmentShader("../src/shaders/main.vs", "../src/shaders/main.fs");

    auto waterShader = std::make_unique<mc::Shader>();
    waterShader->initVertexFragmentShader("../src/shaders/water.vs", "../src/shaders/water.fs");

    std::vector<std::string> faces =
        {
            "../assets/right.jpg",
            "../assets/left.jpg",
            "../assets/top.jpg",
            "../assets/bottom.jpg",
            "../assets/front.jpg",
            "../assets/back.jpg"};
    GLuint cubemapTexture = mc::loadCubemap(faces);
    GLuint skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    auto camera = new mc::Camera(window);

    auto world = new mc::World();
    world->generateChunk(glm::ivec2(0, 0));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(glfwWindow) == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->handleMovement();

        skyboxShader->use();

        blockShader->use();
        blockShader->uniformMat4f("projection", camera->getProjection());
        blockShader->uniformMat4f("view", camera->getView());

        glm::vec3 pos = camera->getPosition();
        float cx = pos.x / 16;
        cx = cx < 0 ? ceil(abs(cx)) * -1 : floor(cx);
        float cz = pos.z / 16;
        cz = cz < 0 ? ceil(abs(cz)) * -1 : floor(cz);
        world->generateChunksAroundPosition({cx, cz});
        world->renderBlockMeshes({cx, cz}, blockShader);
        world->renderWaterMeshes({cx, cz}, waterShader);

        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();
    }

    return 0;
}
