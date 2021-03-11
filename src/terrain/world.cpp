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

void World::generateChunk(glm::ivec2 position)
{
    std::cout << "** Generating Chunk ** " << position.x << '/' << position.y << '\n';
    Chunk *chunk = new Chunk();
    chunk->setPosition(position);
    chunk->setWorld(this);
    chunks[position] = chunk;

    int initialWorldX = position.x * Chunk::CHUNK_SIZE;
    int initialWorldZ = position.y * Chunk::CHUNK_SIZE;

    double slope = 1.0 * (mc::Chunk::CHUNK_HEIGHT - 1 - 0) / (1 + 1);
    int imageIndex = 0;

    for (int x = initialWorldX; x < initialWorldX + Chunk::CHUNK_SIZE; x++)
    {
        for (int z = initialWorldZ; z < initialWorldZ + Chunk::CHUNK_SIZE; z++)
        {
            int finalY = getBlockHeightAtWorldPosition(glm::ivec2(x, z));

            for (int belowY = finalY; belowY >= 0; belowY--)
            {
                BlockType type = BlockType::Stone;
                if (belowY >= finalY - 2)
                {
                    if (belowY < 20)
                    {
                        type = BlockType::Grass;
                    }
                    else
                    {
                        if (belowY < 24)
                        {
                            int canBeGrass = rand() % 10 + 1;
                            if (canBeGrass == 1) // 10% chance
                            {
                                type = BlockType::Grass;
                            }
                        }
                    }
                }
                int blockRelativeToChunkX = x - initialWorldX;
                int blockRelativeToChunkZ = z - initialWorldZ;
                chunk->setBlock(glm::vec3(blockRelativeToChunkX, belowY, blockRelativeToChunkZ), type);
            }
        }
    }

    chunk->createMesh();
}

Chunk *World::getChunk(glm::ivec2 position)
{
    // return chunks[position];
    if (chunks.count(position) == 0)
    {
        return nullptr;
    }
    return chunks[position];
}

void World::render(const std::unique_ptr<Shader> &shader)
{
    for (auto const &[position, chunk] : chunks)
    {
        chunk->render(shader);
    }
}