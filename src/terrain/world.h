#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>
using namespace glm;
#include <stb_image_write.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>

namespace mc
{
    class World;
};

#include "chunk.h"
#include "FastNoiseLite.h"

struct KeyFuncs
{
    size_t operator()(const ivec2 &k) const
    {
        return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
    }

    bool operator()(const ivec2 &a, const ivec2 &b) const
    {
        return a.x == b.x && a.y == b.y;
    }
};

// typedef std::unordered_map<glm::ivec2, int, KeyFuncs, KeyFuncs> MyMap;

namespace mc
{
    class World
    {
    private:
        std::vector<std::vector<float>> heightmap;

        uint_fast32_t seed;

        static const int WIDTH = 256;
        static const int HEIGHT = 256;

        std::unordered_map<glm::ivec2, Chunk *, KeyFuncs, KeyFuncs> chunks;
        // std::vector<Chunk *> chunks;

        FastNoiseLite noise;

        double maxHeight = 32 * 2.0;
        double minHeight = 0.0;

        void generateSeed();

    public:
        World();

        int getBlockHeightAtWorldPosition(glm::ivec2 position)
        {
            float y = noise.GetNoise((float)position.x, (float)position.y);
            int finalY = (int)(((y + 1) / 2.0) * (maxHeight - minHeight));
            return finalY;
        }

        void generateChunk(glm::ivec2 position);
        void render(const std::unique_ptr<Shader> &shader);
        Chunk *getChunk(glm::ivec2 position);
    };

}; // namespace mc

#endif