#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../texture.h"
#include "../rendering/vao.h"
#include "../rendering/vbo.h"
#include "../shader.h"

#include <memory>
#include <map>

namespace mc
{

    enum BlockType
    {
        Air,
        Stone,
        EndStone,
    };

    static std::map<BlockType, Texture> blockTextures;

    class Block
    {
    private:
        BlockType type = BlockType::Air;
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::mat4 modelMatrix = glm::mat4(1.0);

        GLuint vertexArrayID;
        mc::VBO vertexBuffer;
        mc::VBO uvBuffer;
        mc::VBO indicesBuffer;
        mc::VBO normalsBuffer;

        void fillBlockTextureMap();

    public:
        Block();
        // Block(BlockType type, glm::vec3 position);
        // void render(const std::unique_ptr<Shader> &shader);

        void setPosition(glm::vec3 transform) { position = transform; };
        glm::vec3 getPosition() { return position; }
        BlockType getType() { return type; }
        void setType(BlockType bType) { type = bType; }
    };

    static float blockSize = 0.3;

} // namespace  mc

#endif