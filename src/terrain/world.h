#ifndef WORLD_H
#define WORLD_H

#include <glm/glm.hpp>
using namespace glm;
#include <stb_image_write.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <map>

namespace mc
{
    class World;
};

#include "chunk.h"
#include "FastNoiseLite.h"

namespace mc
{
    class World
    {
    private:
        std::vector<std::vector<float>> heightmap;

        uint_fast32_t seed;

        static const int WIDTH = 256;
        static const int HEIGHT = 256;

        // Chunk *chunks;
        std::vector<Chunk *> chunks;
        // std::map<glm::vec3, Chunk *> chunks;

        // Noise1234 *noise = new Noise1234();
        FastNoiseLite noise;
        // FastNoiseSIMD *myNoise = FastNoiseSIMD::NewFastNoiseSIMD();

        void generateSeed();
        double round(double d);

    public:
        World();
        void generateHeightmap();
        void generateChunk(glm::vec3 position);
        void render(const std::unique_ptr<Shader> &shader);
        Chunk *getChunk(glm::vec3 position);
    };

}; // namespace mc

#endif