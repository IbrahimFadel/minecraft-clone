#include "camera.h"

using namespace mc;

void Camera::handleMovement()
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);

    glfwGetCursorPos(window->getGLFWWindow(), &mouseX, &mouseY);
    glfwSetCursorPos(window->getGLFWWindow(), (double)window->getWidth() / 2, (double)window->getHeight() / 2);

    horizontalAngle += sensitivity * deltaTime * float(window->getWidth() / 2 - mouseX);
    verticalAngle += sensitivity * deltaTime * float(window->getHeight() / 2 - mouseY);

    // Move forward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        auto forwardVector = getForwardVector(horizontalAngle) * deltaTime * speed;
        position += forwardVector * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        auto forwardVector = getForwardVector(horizontalAngle) * deltaTime * speed;
        position -= forwardVector * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        auto rightVector = getRightVector(horizontalAngle) * deltaTime * speed;
        position += rightVector * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        auto rightVector = getRightVector(horizontalAngle) * deltaTime * speed;
        position -= rightVector * deltaTime * speed;
    }

    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += glm::vec3(0, 1, 0) * deltaTime * speed;
    }
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        position -= glm::vec3(0, 1, 0) * deltaTime * speed;
    }

    view = glm::lookAt(
        position,                                                       // Camera is here
        position + getLookingDirection(horizontalAngle, verticalAngle), // and looks here : at the same position, plus "direction"
        glm::vec3(0, 1, 0)                                              // Head is up (set to 0,-1,0 to look upside-down)
    );

    lastTime = currentTime;
}