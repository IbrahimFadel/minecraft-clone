#include "player.h"

using namespace mc;

Player::Player(glm::vec3 position, std::unique_ptr<World> &world, std::unique_ptr<Window> &window) : position(position), world(world), window(window)
{
    camera = std::make_unique<mc::Camera>(window);
    updateCameraMatrices();
}

void Player::handleMovement()
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime);

    glfwGetCursorPos(window->getGLFWWindow(), &mouseX, &mouseY);
    glfwSetCursorPos(window->getGLFWWindow(), (double)window->getWidth() / 2, (double)window->getHeight() / 2);

    horizontalAngle += sensitivity * deltaTime * float(1024 / 2 - mouseX);
    verticalAngle += sensitivity * deltaTime * float(768 / 2 - mouseY);

    glm::ivec2 frontBlockPosition = glm::ivec2(floor(position.x), floor(position.z + 1));
    glm::ivec2 backBlockPosition = glm::ivec2(floor(position.x), floor(position.z - 1));
    int frontBlockHeight = world->getBlockHeightAtWorldPosition(frontBlockPosition);
    int backBlockHeight = world->getBlockHeightAtWorldPosition(backBlockPosition);
    int rightBlockHeight = world->getBlockHeightAtWorldPosition(glm::ivec2(round(position.x + 1), round(position.z)));
    int leftBlockHeight = world->getBlockHeightAtWorldPosition(glm::ivec2(round(position.x - 1), round(position.z)));

    glm::vec2 playerPosition = glm::vec2(position.x, position.z);

    // Move forward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {

        auto forwardVector = camera->getForwardVector(horizontalAngle) * deltaTime * speed;
        glm::ivec2 blockpos;
        blockpos = glm::ivec2(floor(position.x) + ceil(forwardVector.x), floor(position.z));

        bool xColliding = (position.x > blockpos.x - blockSize &&
                           position.x < blockpos.x + blockSize &&
                           blockpos.y >= floor(position.y - playerHeight));

        // if (!xColliding)
        // {
        position.x += forwardVector.x;
        // }
        position.z += forwardVector.z;
    }
    // Move backward
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        auto forwardVector = camera->getForwardVector(horizontalAngle) * deltaTime * speed;
        position.x -= forwardVector.x;
        position.z -= forwardVector.z;
        // position -= camera->getForwardVector(horizontalAngle) * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        auto rightVector = camera->getRightVector(horizontalAngle) * deltaTime * speed;
        position.x += rightVector.x;
        position.z += rightVector.z;
        // position += camera->getRightVector(horizontalAngle) * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        auto rightVector = camera->getRightVector(horizontalAngle) * deltaTime * speed;
        position.x -= rightVector.x;
        position.z -= rightVector.z;
        // position -= camera->getRightVector(horizontalAngle) * deltaTime * speed;
    }

    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        // if (!notTouchingGround())
        // {
        velocity.y = jumpVelocity;
        position.y += velocity.y * deltaTime;
        // }
    }
    if (glfwGetKey(window->getGLFWWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        // if (!notTouchingGround())
        // {
        velocity.y = jumpVelocity;
        position.y -= velocity.y * deltaTime;
        // }
    }

    // if (velocity.x > 0)
    // {
    //     if (velocity.x - 1 < 0)
    //     {
    //         velocity.x = 0;
    //     }
    //     else
    //     {
    //         velocity.x -= 1;
    //     }
    // }

    // // velocity.x = 0;
    // // velocity.z = 0;

    // if (velocity.z > 0)
    // {
    //     if (velocity.z - 1 < 0)
    //     {
    //         velocity.z = 0;
    //     }
    //     else
    //     {
    //         velocity.z -= 1;
    //     }
    // }

    // fall();

    lastTime = currentTime;
}

void Player::fall()
{
    if (notTouchingGround())
    {
        velocity.y += gravity * deltaTime;
        position.y += velocity.y * deltaTime;
    }
}

void Player::updateCameraMatrices()
{
    camera->setPosition(position);

    lookingDirection = camera->getLookingDirection(horizontalAngle, verticalAngle);
    camera->setProjection(FOV, 4.0f / 3.0f, 0.1f, 300.0f);
    camera->lookAt(lookingDirection, glm::cross(camera->getRightVector(horizontalAngle), lookingDirection));
}