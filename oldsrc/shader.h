#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace mc
{
    class Shader
    {
    private:
        GLuint program;

        std::string getFileContent(const char *path);

    public:
        void initVertexFragmentShader(const char *vPath, const char *fPath);

        void use();
        void uniform2f(const char *uniformName, float v1, float v2);
        void uniform1i(const char *uniformName, int v);
        void uniformMat4f(const char *uniformName, glm::mat4);
    };
}; // namespace mc

#endif