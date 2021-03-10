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

void Window::run(void (*renderFunction)())
{
    while (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(glfwWindow) == 0)
    {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glUseProgram(programID);

        // // Draw nothing, see you in tutorial 2 !
        // // 1st attribute buffer : vertices
        // glEnableVertexAttribArray(0);
        // glBindBuffer(GL_ARRAY_BUFFER, buf);
        // glVertexAttribPointer(
        //     0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        //     3,        // size
        //     GL_FLOAT, // type
        //     GL_FALSE, // normalized?
        //     0,        // stride
        //     (void *)0 // array buffer offset
        // );
        // // Draw the triangle !
        // glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        // glDisableVertexAttribArray(0);

        // Swap buffers
        glfwSwapBuffers(glfwWindow);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
}