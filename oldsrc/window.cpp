#include "window.h"

#include <iostream>
using std::cout;

using namespace mc;

void Window::initWindow()
{
    GLFWwindow *_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (_window == NULL)
    {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        glfwTerminate();
        exit(1);
    }
    glfwWindow = _window;
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
