#include "world.h"

#include <random>

using namespace mc;

World::World()
{
    generateSeed();

    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(seed);
    noise.SetFrequency(0.02);
}

void World::generateSeed()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, WIDTH); // distribution in range [1, 6]
    seed = dist6(rng);
}

double World::round(double d)
{
    return floor(d + 0.5);
}

void World::generateHeightmap()
{
    // noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    char imageData[Chunk::CHUNK_SIZE * 4 * Chunk::CHUNK_SIZE * 4 * 3];
    int index = 0;
    int imageIndex = 0;

    double maxHeight = 32 * 2.0;
    double minHeight = 0.0;

    for (int x = 0; x < Chunk::CHUNK_SIZE * 4; x++)
    {
        for (int z = 0; z < Chunk::CHUNK_SIZE * 4; z++)
        {
            float y = noise.GetNoise((float)x, (float)z);

            int output = (int)(((y + 1) / 2.0) * (maxHeight - minHeight));
            imageData[imageIndex++] = output;
            imageData[imageIndex++] = output;
            imageData[imageIndex++] = output;
        }
    }

    stbi_write_png("../image_out.png", Chunk::CHUNK_SIZE * 4, Chunk::CHUNK_SIZE * 4, 3, imageData, Chunk::CHUNK_SIZE * 4 * 3);
}

void World::generateChunk(glm::vec3 position)
{
    std::cout << "** Generating Chunk ** " << position.x << '/' << position.y << '/' << position.z << '\n';
    Chunk *chunk = new Chunk();
    chunk->setPosition(position);
    chunk->setWorld(this);
    chunks.push_back(chunk);

    int initialWorldX = position.x * Chunk::CHUNK_SIZE;
    int initialWorldZ = position.z * Chunk::CHUNK_SIZE;

    double slope = 1.0 * (mc::Chunk::CHUNK_HEIGHT - 1 - 0) / (1 + 1);
    // char imageData[Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE * 3];
    int imageIndex = 0;

    double maxHeight = 32 * 2.0;
    double minHeight = 0.0;

    // 16 -> 32
    // 0 -> 16
    for (int x = initialWorldX; x < initialWorldX + Chunk::CHUNK_SIZE; x++)
    {
        for (int z = initialWorldZ; z < initialWorldZ + Chunk::CHUNK_SIZE; z++)
        {
            // int blockWorldX = initialWorldX * Chunk::CHUNK_SIZE + x;
            // int blockWorldZ = initialWorldZ * Chunk::CHUNK_SIZE + z;
            float y = noise.GetNoise((float)x, (float)z);

            int finalY = (int)(((y + 1) / 2.0) * (maxHeight - minHeight));

            // int finalY = round(slope * (y + 1));

            // imageData[imageIndex++] = finalY;
            // imageData[imageIndex++] = finalY;
            // imageData[imageIndex++] = finalY;

            for (int belowY = finalY; belowY >= 0; belowY--)
            {
                int blockRelativeToChunkX = x - initialWorldX;
                int blockRelativeToChunkZ = z - initialWorldZ;
                chunk->setBlock(glm::vec3(blockRelativeToChunkX, belowY, blockRelativeToChunkZ), BlockType::Stone);
            }
        }
    }

    chunk->createMesh();
    // stbi_write_png("../chunk.png", Chunk::CHUNK_SIZE, Chunk::CHUNK_SIZE, 3, imageData, Chunk::CHUNK_SIZE * 3);
}

Chunk *World::getChunk(glm::vec3 position)
{
    for (auto const &chunk : chunks)
    {
        auto pos = chunk->getPosition();
        if (position == pos)
        {
            return chunk;
        }
    }
    return nullptr;
}

void World::render(const std::unique_ptr<Shader> &shader)
{
    for (auto const &chunk : chunks)
    {
        chunk->render(shader);
    }
}