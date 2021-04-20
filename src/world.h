#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>
using namespace glm;

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

        int waterLevel = 15;

        double maxHeight = 32 * 2.0;
        double minHeight = 0.0;
        int lacunarity = 15;     // controls increase in frequency of octaves
        float persistance = 0.5; // controls decrease in amplitude of octaves
        int numOctaves = 8;
        int renderDistance = 5;

        void generateSeed();

    public:
        World();

        int getBlockHeightAtWorldPosition(glm::ivec2 position)
        {
            float amplitude = 1;
            float frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < numOctaves; i++)
            {
                // noise.SetFrequency(pow(lacunarity, i));
                // amplitude = pow(persistance, i);
                float y = noise.GetNoise((float)position.x, (float)position.y);
                float finalY = (((y + 1) / 2.0) * ((amplitude * 30) - minHeight));
                noiseHeight += finalY;
                // std::cout << y << ' ' << finalY << ' ' << noiseHeight << '\n';

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            return noiseHeight;
        }

        void renderBlockMeshes(ivec2 pos, const std::unique_ptr<Shader> &shader);
        void renderWaterMeshes(ivec2 pos, const std::unique_ptr<Shader> &shader);

        bool chunkInRenderDistance(ivec2 cameraPos, ivec2 pos);
        void generateChunksAroundPosition(glm::ivec2 position);
        void generateChunk(glm::ivec2 position);
        Chunk *getChunk(glm::ivec2 position);
        BlockType getBlock(glm::ivec3 position);

        std::unordered_map<glm::ivec2, Chunk *, KeyFuncs, KeyFuncs> getChunks() { return chunks; }
    };

}; // namespace mc

#endif