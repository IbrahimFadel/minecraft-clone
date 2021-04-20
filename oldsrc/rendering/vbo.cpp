#include "vbo.h"

mc::VBO mc::createVBO(GLint type, int size, VBODataType dataType)
{
    mc::VBO vbo;
    vbo.type = type;
    vbo.size = size;
    vbo.dataType = dataType;
    glGenBuffers(1, &vbo.handle);
    return vbo;
}

void mc::bindVBO(mc::VBO vbo)
{
    glBindBuffer(vbo.type, vbo.handle);
}

void mc::destroyVBO(VBO vbo)
{
    glDeleteBuffers(1, &vbo.handle);
}

void mc::vboBuffer(VBO vbo, size_t size, void *first)
{
    bindVBO(vbo);
    glBufferData(vbo.type, size, first, GL_STATIC_DRAW);
}