#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "terrain/world.h"

namespace mc
{
    class Player
    {
    private:
        glm::vec3 position;
        glm::vec3 velocity;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<Window> &window;
        std::unique_ptr<World> &world;

        glm::vec3 lookingDirection;

        float deltaTime;
        float horizontalAngle = 3.14;
        float verticalAngle = 0.0;
        // float speed = 5.0;
        float speed = 15.0;
        float sensitivity = 0.05;
        double mouseX, mouseY;
        float FOV = 45.0;

        float gravity = -9.81;
        // float jumpVelocity = 6.0f;
        float jumpVelocity = 15.0f;

    public:
        Player(glm::vec3 position, std::unique_ptr<World> &world, std::unique_ptr<Window> &window);

        static const int playerHeight = 2;

        bool notTouchingGround()
        {
            int blockY = world->getBlockHeightAtWorldPosition(glm::ivec2(round(position.x), round(position.z)));
            return round(position.y) > blockY + playerHeight;
        }

        const std::unique_ptr<Camera> &getCamera() { return camera; }
        void handleMovement();
        void fall();
        void updateCameraMatrices();
    };
}; // namespace mc

#endif