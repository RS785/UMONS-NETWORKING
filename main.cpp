#pragma once
#include "assert.h"
#include "stdio.h"
#include "iostream"
#include "Network.h"
#include "string.h"
#include "thread"

#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
#include <stdbool.h>
#include <thread>
//#define GLFW_INCLUDE_NONE
#include "glad.h"
#include "Window.h"
//#include "glad.h"

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                { -0.6f, -0.4f, 1.f, 0.f, 0.f },
                {  0.6f, -0.4f, 0.f, 1.f, 0.f },
                {   0.f,  0.6f, 0.f, 0.f, 1.f }
        };

static const char* vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

static const char* fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

void teestt(){

}

bool isServer = false;
int main(int argc, char *argv[]){
    Window window(640, 480, "Test Window :)");
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    Network network;

    //std::thread NEW(teestt);
    //NEW.join();

    std::cout << argc << std::endl;
    //network.init();
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-server") == 0) {
            isServer = true;
        }
    }

    glfwMakeContextCurrent(window.window);
    gladLoadGL();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
/*    program = glCreateProgram();
    glLinkProgram(program);*/

    //gladLoadGL();
    glfwSwapInterval(1);


    /*glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));*/


    while(!window.ShouldClose())
    {
        int width, height;
        glfwGetFramebufferSize(window.window, &width, &height);
        //
        glad_glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }

    glfwTerminate();
/*    if(isServer)
        network.runServer();
    else
        network.runClient();*/
    exit(EXIT_SUCCESS);
}