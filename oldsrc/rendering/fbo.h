#ifndef FBO_H
#define FBO_H

#include <GL/glew.h>

namespace mc
{
    GLuint createFBO();
    void bindFBO(GLuint);
    void bindDefaultFBO();
    void destroyFBO(GLuint fbo);
    void attachTextureToFBO(GLuint texture);
    void attachRenderBuffer(GLuint rbo);

    GLuint createRBO();
    void bindRBO(GLuint rbo);
    void createDepthBufferAttachment(int width, int height);
}; // namespace mc

#endif