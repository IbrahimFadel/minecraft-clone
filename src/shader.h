#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>

namespace mc
{
    class Shader
    {
    private:
        const char *vertexFilePath;
        const char *fragmentFilePath;

        GLuint programID;

    public:
        Shader(const char *vertexFilePath, const char *fragmentFilePath) : vertexFilePath(vertexFilePath), fragmentFilePath(fragmentFilePath){};

        void load();
        GLuint getProgramID() { return programID; }
    };
} // namespace mc

#endif