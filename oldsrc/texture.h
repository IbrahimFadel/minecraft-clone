#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <cstring>
#include <cassert>

#include <stb_image.h>

namespace mc
{
    struct Texture
    {
        GLuint handle;
        int width, height;
    };

    void loadTexturePixels(const char *path, unsigned char **pixels, size_t *width, size_t *height);
    Texture createTextureFromPixels(unsigned char *pixels, size_t width, size_t height);
    Texture createTextureFromPath(const char *path);

}; // namespace mc

#endif