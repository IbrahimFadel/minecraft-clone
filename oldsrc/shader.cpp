#include "shader.h"

using namespace mc;

std::string Shader::getFileContent(const char *path)
{
    std::string fileContent;
    std::ifstream fStream(path, std::ios::in);
    if (fStream.is_open())
    {
        std::stringstream sstr;
        sstr << fStream.rdbuf();
        fileContent = sstr.str();
        fStream.close();
    }
    else
    {
        std::cerr << "Could not open " << path << "\n";
        exit(1);
    }

    return fileContent;
}

void Shader::initVertexFragmentShader(const char *vPath, const char *fPath)
{
    auto vsContent = getFileContent(vPath);
    const char *vsSource = vsContent.c_str();
    auto fsContent = getFileContent(fPath);
    const char *fsSource = fsContent.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    GLint isCompiled = 0;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vs, maxLength, &maxLength, &errorLog[0]);

        printf("%s\n", &errorLog[0]);

        glDeleteShader(vs);
        return;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);

    isCompiled = 0;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fs, maxLength, &maxLength, &errorLog[0]);

        printf("%s\n", &errorLog[0]);

        glDeleteShader(fs);
        return;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    program = prog;
}

void Shader::use()
{
    glUseProgram(program);
}

void Shader::uniform2f(const char *uniformName, float v1, float v2)
{
    glUniform2f(glGetUniformLocation(program, uniformName), v1, v2);
}

void Shader::uniform1i(const char *uniformName, int v)
{
    glUniform1i(glGetUniformLocation(program, uniformName), v);
}

void Shader::uniformMat4f(const char *uniformName, glm::mat4 mat)
{
    glUniformMatrix4fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, &mat[0][0]);
}