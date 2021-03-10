#include "camera.h"

using namespace mc;

void Camera::computeMatricesFromInputs()
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    glfwGetCursorPos(window->getGLFWWindow(), &mouse.xpos, &mouse.ypos);
    glfwSetCursorPos(window->getGLFWWindow(), (double)window->getWidth() / 2, (double)window->getHeight() / 2);

    horizontalAngle += mouse.speed * deltaTime * float(1024 / 2 - mouse.xpos);
    verticalAngle += mouse.speed * deltaTime * float(768 / 2 - mouse.ypos);

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle));

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f));

    glm::vec3 directionNoY = glm::vec3(
        sin(horizontalAngle),
        0,
        cos(horizontalAngle));

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        // position += direction * deltaTime * speed;
        position += directionNoY * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        // position -= direction * deltaTime * speed;
        position -= directionNoY * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= right * deltaTime * speed;
    }
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += vec3(0, 1, 0) * deltaTime * speed;
    }
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        position -= vec3(0, 1, 0) * deltaTime * speed;
    }

    float FoV = initialFOV; // - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    // Camera matrix
    view = glm::lookAt(
        position,             // Camera is here
        position + direction, // and looks here : at the same position, plus "direction"
        up                    // Head is up (set to 0,-1,0 to look upside-down)
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}