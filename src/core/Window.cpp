#include <Crunch/core/Window.hpp>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

namespace Crunch {

bool Window::init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "error: fatal: failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      // OpenGL Version 3.3 Core

    /*
        Most system will work fine, but Apple depreciated OpenGL in 2019,
        so we enable forward compatibility to make sure it works properly without fault
    */
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_OPENGL_FORWARD_COMPAT);
#endif      // __APPLE__

    return true;
}

void Window::create(int w, int h, const char* title) {
    // Save the window details for later use
    _width = w;
    _height = h;
    _title = title;

    // Create the window & initialize GLAD
    _window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!_window) {
        // The window is NULL, and an error occurred
        std::cout << "error: fatal: failed to create OpenGL window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(_window);                // Need to make the context current ready for GLAD

    // Initialize GLAD loader. This is essential for rendering
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // GLAD failed to load
        std::cout << "error: fatal: failed to load GLAD" << std::endl;
        return;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Set the framebuffer size callback
    // This function is called every time the window is resized
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

bool Window::windowShouldClose() {
    // Should the window close or not?
    // This is used in the main loop, so that when the user clicks the close button, the application actually closes
    return glfwWindowShouldClose(_window);
}

void Window::update() {
    // Poll events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void Window::clear(glm::vec4 color) {
    // Clear the screen to the color specified in the call
    // We clear the depth buffer as well, since depth testing is enabled
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::getWindow() {
    // Just return the window type
    return _window;
}


/*
    Private helper functions/callbacks
*/
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}
