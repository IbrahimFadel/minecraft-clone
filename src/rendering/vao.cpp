#include "vao.h"

GLuint mc::createVAO()
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    return vao;
}

void mc::bindVAO(GLuint vao)
{
    glBindVertexArray(vao);
}

void mc::destroyVAO(GLuint vao)
{
    glDeleteVertexArrays(1, &vao);
}

void mc::vaoEnable(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
}
