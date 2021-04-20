#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include <GL/glew.h>

namespace mc
{
    GLuint createVAO();
    void bindVAO(GLuint vao);
    void destroyVAO(GLuint vao);
    void vaoEnable(GLuint index, GLint size, VBODataType dataType, GLsizei stride, size_t offset);
}; // namespace mc

#endif