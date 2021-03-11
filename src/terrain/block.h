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
        Grass,
        Stone,
        EndStone,
    };

    static const int blockatlasWidth = 96;
    static const int textureSize = 16;
    static const int numTexturesInAtlas = blockatlasWidth / textureSize;

    static std::map<BlockType, int> blockTextureOffsets = {
        {BlockType::Grass, 0},
        {BlockType::Stone, 2},
    };

    static float blockSize = 0.3;

} // namespace  mc

#endif