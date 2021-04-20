#ifndef BLOCK_H
#define BLOCK_H

#include <map>

namespace mc
{

    enum BlockType
    {
        Air,
        Grass,
        Stone,
        Water,
        EndStone,
    };

    static const int blockatlasWidth = 96;
    static const int textureSize = 16;
    static const int numTexturesInAtlas = blockatlasWidth / textureSize;

    static std::map<BlockType, int> blockTextureOffsets = {
        {BlockType::Grass, 0},
        {BlockType::Stone, 2},
        {BlockType::Water, 3},
    };

    static float blockSize = 0.3;

} // namespace  mc

#endif