#include "fbo.h"

using namespace mc;

GLuint mc::createFBO()
{
    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    return fbo;
}

void mc::bindFBO(GLuint fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void mc::bindDefaultFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void mc::destroyFBO(GLuint fbo)
{
    glDeleteFramebuffers(1, &fbo);
}

void mc::attachTextureToFBO(GLuint texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0); //? Possibly attach depth and stencil buffers aswell
}

GLuint mc::createRBO()
{
    GLuint rbo;
    glGenRenderbuffers(1, &rbo);
    return rbo;
}

void mc::bindRBO(GLuint rbo)
{
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
}

void mc::createDepthBufferAttachment(int width, int height)
{
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
}

void attachRenderBuffer(GLuint rbo)
{
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
}