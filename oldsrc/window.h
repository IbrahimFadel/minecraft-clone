#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

namespace mc
{
    class Window
    {
    private:
        unsigned width;
        unsigned height;
        std::string title;
        GLFWwindow *glfwWindow;

        void initWindow();

    public:
        Window(unsigned width, unsigned height, std::string title) : width(width), height(height), title(title) { initWindow(); };

        GLFWwindow *getGLFWWindow() { return glfwWindow; }
        unsigned getWidth() { return width; }
        unsigned getHeight() { return height; }
    };
} // namespace mc

#endif