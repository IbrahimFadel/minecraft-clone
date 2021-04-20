#include "texture.h"

void mc::loadTexturePixels(const char *path, unsigned char **_pixels, size_t *_width, size_t *_height)
{
    int width, height, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    assert(image != NULL);

    *_pixels = (unsigned char *)malloc(width * height * 4);
    memcpy(*_pixels, image, width * height * 4);
    *_width = width;
    *_height = height;

    stbi_image_free(image);
}

mc::Texture mc::createTextureFromPixels(unsigned char *pixels, size_t width, size_t height)
{
    Texture tex;
    tex.width = width;
    tex.height = height;

    glGenTextures(1, &tex.handle);
    glBindTexture(GL_TEXTURE_2D, tex.handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    return tex;
}

mc::Texture mc::createTextureFromPath(const char *path)
{
    unsigned char *pixels;
    size_t width, height;
    loadTexturePixels(path, &pixels, &width, &height);
    Texture tex = createTextureFromPixels(pixels, width, height);
    return tex;
}