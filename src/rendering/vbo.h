#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

namespace mc
{
    struct VBO
    {
        GLint type;
        GLuint handle;
        int size;
    };

    VBO createVBO(GLint type, int size);
    void bindVBO(VBO vbo);
    void destroyVBO(VBO vbo);
    void vboBuffer(VBO vbo, size_t size, void *first);
} // namespace  mc

#endif