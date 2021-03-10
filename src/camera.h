#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"

namespace mc
{
    struct Mouse
    {
        double xpos, ypos;
        float speed = 0.03;
    };

    class Camera
    {
    private:
        std::unique_ptr<mc::Window> &window;

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(
            glm::vec3(4, 1, 5),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));

        glm::vec3 position = glm::vec3(0, 0, 0);
        float horizontalAngle = 3.14;
        float verticalAngle = 0.0;
        float initialFOV = 45.0;
        float speed = 15.0;

        Mouse mouse;

    public:
        Camera(std::unique_ptr<mc::Window> &window) : window(window){};
        void computeMatricesFromInputs();

        glm::mat4 getView() { return view; }
        glm::mat4 getProjection() { return projection; }
        glm::vec3 getPosition() { return position; }
    }; // namespace mc
};     // namespace mc

#endif