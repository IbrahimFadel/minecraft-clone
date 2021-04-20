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

void mc::vaoEnable(GLuint index, GLint size, VBODataType dataType, GLsizei stride, size_t offset)
{
    glEnableVertexAttribArray(index);
    switch (dataType)
    {
    case VBODataType::Float:
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void *)offset);
        break;
    case VBODataType::UnsignedInt:
        glVertexAttribPointer(index, size, GL_UNSIGNED_INT, GL_FALSE, stride, (void *)offset);
        break;
    case VBODataType::UnsignedInt8:
        // glVertexAttribPointer(index, size, GL_UNSIGNED_BYTE, GL_FALSE, stride, (void *)offset);
        glVertexAttribIPointer(index, size, GL_UNSIGNED_BYTE, stride, (void *)offset);
        break;
    case VBODataType::Bool:
        glVertexAttribPointer(index, size, GL_BOOL, GL_FALSE, stride, (void *)offset);
        break;
    default:
        break;
    }
}
