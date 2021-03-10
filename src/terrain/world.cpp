#include "world.h"

#include <random>

using namespace mc;

World::World()
{
    generateSeed();
}

void World::generateSeed()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, WIDTH); // distribution in range [1, 6]
    seed = dist6(rng);
}

float World::turbulence(vec2 Q)
{
    // std::cout << Q.x << '/' << Q.y << '\n';
    // return noise->noise((float)Q.x / WIDTH, (float)Q.y / WIDTH, (float)seed);
    // return noise->noise((float)Q.x * 0.3f, (float)Q.y * 0.3f, (float)seed) * 2.f;
    // return noise->noise((float)Q.x * 0.1f, (float)Q.y * 0.1f, (float)seed);
    // float value = 0;
    // for (float f = 1; f < 15; f *= 2)
    // {
    //     value += abs(noise->noise(Q.x * f, Q.y * f)) / f;
    // }
    // return value;
}

double World::round(double d)
{
    return floor(d + 0.5);
}

void World::generateHeightmap()
{
    // noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(seed);
    noise.SetFrequency(0.04);

    char imageData[WIDTH * WIDTH * 3];
    int index = 0;
    int imageIndex = 0;

    // double slope = (255 - 1) / (1 - 0);
    double slope = 1.0 * (255 - 0) / (1 - -1);
    double slopeMC = 1.0 * (15 - 0) / (1 - -1);

    for (int y = 0; y < WIDTH; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            float val = noise.GetNoise((float)x, (float)y);
            double fake = 0 + World::round(slopeMC * (val - -1));
            double output = 0 + World::round(slope * (fake - -1));
            // float output = 1 + slope * (val - 0);
            // std::cout << (int)round(fake) << '\n';
            imageData[imageIndex++] = output;
            imageData[imageIndex++] = output;
            imageData[imageIndex++] = output;
        }
    }

    stbi_write_png("../image_out3.png", WIDTH, HEIGHT, 3, imageData, WIDTH * 3);
}

void World::generateChunk(glm::vec3 position)
{
    std::cout << "CHUNK: " << position.x << '/' << position.y << '/' << position.z << '\n';
    Chunk *chunk = new Chunk();
    chunk->setPosition(position);
    chunk->setWorld(this);
    chunks.push_back(chunk);

    std::cout << chunk << '\n';

    int initialWorldX = position.x * Chunk::CHUNK_SIZE;
    int initialWorldY = position.y;
    int initialWorldZ = position.z * Chunk::CHUNK_SIZE;

    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetSeed(seed);
    noise.SetFrequency(0.01);

    float *noiseData = new float[Chunk::CHUNK_SIZE * Chunk::CHUNK_SIZE];
    int index = 0;

    // double slope = (Chunk::CHUNK_SIZE - 1 - 0) / (1 - 0);
    double slope = 1.0 * (mc::Chunk::CHUNK_SIZE - 1 - 0) / (1 - -1);
    // 1.0 * (output_end - output_start) / (input_end - input_start)
    // double slopeMC = 1.0 * (15 - 0) / (1 - -1);

    // for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
    // {
    //     for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
    //     {
    //         int blockWorldX = initialWorldX * Chunk::CHUNK_SIZE + x;
    //         int blockWorldZ = initialWorldZ * Chunk::CHUNK_SIZE + z;
    //         float y = noiseData[index++] = noise.GetNoise((float)blockWorldX, (float)blockWorldZ);
    //         // float output = 1 + slope * (y - 0);
    //         float output = 0 + round(slope * (y - -1));
    //         int finalY = round(output);
    //         // int finalY = round(y + 1) * 7;
    //         // int finalY = (int)(0 + World::round(slope * (y - -1)));
    //         // y = (y + 1) / 2;
    //         // float output = 1 + slope * (y - 0);
    //         // int finalY = round(output);

    //         // std::cout << x << '/' << finalY << '/' << z << '\n';
    //         // finalY = Chunk::CHUNK_SIZE - 1;
    //         // for (int belowY = finalY; belowY >= 0; belowY--)
    //         // {
    //         // chunk->setBlock(glm::vec3(x, finalY, z), BlockType::Stone);
    //         // chunk->setBlock(glm::vec3(x, finalY - 1, z), BlockType::Stone);
    //         // chunk->setBlock(glm::vec3(x, finalY - 2, z), BlockType::Stone);
    //         // chunk->setBlock(glm::vec3(x, finalY - 3, z), BlockType::Stone);
    //         // chunk->setBlock(glm::vec3(x, belowY, z), BlockType::Stone);
    //         // }
    //     }
    // }

    delete[] noiseData;

    chunk->createMesh();
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