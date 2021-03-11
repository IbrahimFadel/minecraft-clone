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
    class Camera
    {
    private:
        std::unique_ptr<mc::Window> &window;

        glm::mat4 projection = glm::perspective(glm::radians(65.0f), (float)window->getWidth() / (float)window->getHeight(), 0.1f, 1000.0f);
        glm::mat4 view = glm::lookAt(
            glm::vec3(4, 1, 5),
            glm::vec3(0, 0, 0),
            glm::vec3(0, 1, 0));

        glm::vec3 position = glm::vec3(0, 32, 0);

    public:
        Camera(std::unique_ptr<mc::Window> &window) : window(window){};

        glm::vec3 getRightVector(float ha)
        {
            return glm::vec3(
                sin(ha - 3.14f / 2.0f),
                0,
                cos(ha - 3.14f / 2.0f));
        }
        glm::vec3 getForwardVector(float ha)
        {
            return glm::vec3(
                sin(ha),
                0,
                cos(ha));
        }

        glm::vec3 getLookingDirection(float ha, float va)
        {
            return glm::vec3(cos(va) * sin(ha),
                             sin(va),
                             cos(va) * cos(ha));
        }

        void lookAt(glm::vec3 direction, glm::vec3 up)
        {
            view = glm::lookAt(
                position,             // Camera is here
                position + direction, // and looks here : at the same position, plus "direction"
                up                    // Head is up (set to 0,-1,0 to look upside-down)
            );
        }

        void setProjection(float fov, float aspectRatio, float near, float far)
        {
            projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
        }
        void setPosition(glm::vec3 pos) { position = pos; }
        glm::mat4 getView() { return view; }
        glm::mat4 getProjection() { return projection; }
        glm::vec3 getPosition() { return position; }
    }; // namespace mc
};     // namespace mc

#endif