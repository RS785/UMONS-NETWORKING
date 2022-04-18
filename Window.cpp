#include "Window.h"
#include "assert.h"

Window::Window(int w, int h, std::string name) : width{w}, height{h}, windowName{name}{
    initWindow();
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    //glfwWindowHint(GLFW_OPENGL_API, GLFW_TRUE);

/*    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);*/
/*    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
/*    if(!window){
        assert
    }*/

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, framebufferResizedCallback);
    glfwMakeContextCurrent(window);
}

void Window::framebufferResizedCallback(GLFWwindow *window, int width, int height) {
    auto _window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    _window->framebufferResized = true;
    _window->width = width;
    _window->height = height;
}
