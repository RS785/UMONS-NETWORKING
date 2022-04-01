#ifndef NETWORKING_WINDOW_H
#define NETWORKING_WINDOW_H

#include "string"
#include "GLFW/glfw3.h"

class Window {

public:
    Window(int w, int h, std::string name);
    ~Window();

    GLFWwindow *window;
    GLFWwindow* getGLFWWindow() const { return window; }

    bool ShouldClose() { return glfwWindowShouldClose(window); }

private:

    void initWindow();
    int width, height;
    std::string windowName;
    bool framebufferResized = false;

    static void framebufferResizedCallback(GLFWwindow* window, int width, int height);

};


#endif //NETWORKING_WINDOW_H
