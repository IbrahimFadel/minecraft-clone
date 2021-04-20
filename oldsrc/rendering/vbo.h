#ifndef VBO_H
#define VBO_H

#include <GL/glew.h>

namespace mc
{
    enum VBODataType
    {
        Float,
        Bool,
        UnsignedInt,
        UnsignedInt8
    };
    struct VBO
    {
        GLint type;
        GLuint handle;
        VBODataType dataType;
        int size;
    };

    VBO createVBO(GLint type, int size, VBODataType dataType);
    void bindVBO(VBO vbo);
    void destroyVBO(VBO vbo);
    void vboBuffer(VBO vbo, size_t size, void *first);
} // namespace  mc

#endif