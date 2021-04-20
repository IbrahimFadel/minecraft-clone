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
            int blockRelativeToChunkX = x - initialWorldX;
            int blockRelativeToChunkZ = z - initialWorldZ;

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
                chunk->setBlock(glm::vec3(blockRelativeToChunkX, belowY, blockRelativeToChunkZ), type);
            }
            if (finalY <= waterLevel)
            {
                for (int aboveY = finalY; aboveY < waterLevel; aboveY++)
                {
                    chunk->setBlock(glm::vec3(blockRelativeToChunkX, aboveY, blockRelativeToChunkZ), BlockType::Water);
                }
            }
        }
    }

    chunk->createMesh();
}

Chunk *World::getChunk(glm::ivec2 position)
{
    if (chunks.count(position) == 0)
    {
        return nullptr;
    }
    return chunks[position];
}

void World::render(Renderer *renderer)
{
    for (auto const &[position, chunk] : chunks)
    {
        // chunk->render(renderer);
        chunk->renderBlockMesh(renderer);
        // chunk->renderWaterMesh(renderer);
    }
}

BlockType World::getBlock(glm::ivec3 position)
{
    float cx = position.x / 16;
    cx = cx < 0 ? ceil(abs(cx)) * -1 : floor(cx);
    float cz = position.z / 16;
    cz = cz < 0 ? ceil(abs(cz)) * -1 : floor(cz);

    std::cout << cx << '/' << cz << '\n';

    Chunk *chunk = getChunk(glm::ivec2((int)cx, (int)cz));
    if (!chunk)
    {
        std::cout << "NOT OKAY\n";
        // return chunk->getBlock(glm::ivec3(position.x - (int)(cx * Chunk::CHUNK_SIZE), position.y, position.z - (int)(cz * Chunk::CHUNK_SIZE)));
    }

    int cubeChunkX = position.x - (int)(cx * Chunk::CHUNK_SIZE);
    int cubeChunkZ = position.z - (int)(cz * Chunk::CHUNK_SIZE);
    // std::cout << cubeChunkX << '/' << cubeChunkZ << '\n';

    return chunk->getBlock(glm::ivec3(position.x - (int)(cx * Chunk::CHUNK_SIZE), position.y, position.z - (int)(cz * Chunk::CHUNK_SIZE)));
}