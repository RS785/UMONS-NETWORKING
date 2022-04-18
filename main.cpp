#pragma once
#include "assert.h"
#include "stdio.h"
#include "iostream"
#include "Network.h"
#include "string.h"
#include "thread"


#include <stdbool.h>
#include <thread>
#include "future"
#include <gl/GL.h>
#include "glm/glm.hpp"

#define GLFW_INCLUDE_NONE
//#include "glad.h"
#include "Window.h"
#include "net_client.h"
//#include "gl/GL.h"
//#include "glad.h"


/*class CustomClient : public net::client_interface<net::CustomMsgTypes>{
public:
    void FireBullet(glm::vec3 dir){
        net::message<net::CustomMsgTypes> msg;
        msg.header.id = net::CustomMsgTypes::MovePlayer;
        msg << dir;
    }
};*/

/*enum class CustomMsgTypes : uint32_t {
    MovePlayer,
    FireBullet
};*/

class CustomServer : public net::server_interface<CustomMsgTypes>{
public:
/*    void PingServer(){
        net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }*/
};

class CustomClient : public net::client_interface<CustomMsgTypes>{
public:
    void PingServer(){
        net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow << timeNow;
        Send(msg);
    }
};

Network network;
bool isServer = false;
void runBackground(){
/*    CustomServer cServer;
    CustomClient cClient;*/

    network.init();
    if(isServer){

        //net::server_interface<net::CustomMsgTypes> test(reinterpret_cast<sockaddr_in &>(addr));
        network.runServer();
    }
    else{
        network.runClient();
    }
    return;
/*    if(isServer){
        struct sockaddr_in* addr{};
        CustomServer cServer;
        cServer.Start();
        //net::server_interface<net::CustomMsgTypes> test(reinterpret_cast<sockaddr_in &>(addr));
        //network.runServer(cServer);
    }
    else{
        struct sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY*//*ntohl(addr.address)*//*;
        addr.sin_port = htons( (unsigned short) PORT );

        CustomClient cClient;
        cClient.Connect(addr);
        cClient.PingServer();
        //network.runClient();
    }*/
}

int main(int argc, char *argv[]){

/*    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;*/


    //std::thread NEW(teestt);
    //NEW.join();

/*    char* testBuff = new char[1024];

    const char *LOLTEXT = "1234TESTSTRING";
    int writeL = strnlen(LOLTEXT, 1024);
    for(int w = 0; w < writeL; w++){
        testBuff[w + 10] << LOLTEXT[w];
    }

    testBuff |= "test";*/
/*    testBuff[0] = 'a';
    testBuff[1] = 'b';*/

    uint32_t testS = 69;
    //strncpy_s(testBuff, , sizeof (testBuff) - 1);
    //std::cout << testBuff << std::endl;
    //testBuff << (char*)testS;
    //testBuff << (char*)testS;

    uint8_t packet_data[32];
    memset( packet_data, 0, sizeof( packet_data ) );


    char* title = "Client";
    //network.init();
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-server") == 0) {
            isServer = true;
            title = "Server";
        }
    }
    std::thread newThreadLOL(runBackground);


    /*    int res = gladLoadGL();
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);*/
/*    program = glCreateProgram();
    glLinkProgram(program);*/

    //gladLoadGL();
    //glfwSwapInterval(1);


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


/*    GLFWwindow* window;
    glfwInit();
    window = glfwCreateWindow(640, 480, "AHAHAHA", NULL, NULL);*/

    Window window(640, 480, title);
    glfwMakeContextCurrent(window.getGLFWWindow());
    //glfwMakeContextCurrent(window);

    int fPressed = false;
    while(!window.ShouldClose())
    //while(!glfwWindowShouldClose(window))
    {

        if(glfwGetKey(window.window, GLFW_KEY_F) == GLFW_PRESS)
            fPressed = true;
        if(glfwGetKey(window.window, GLFW_KEY_F) == GLFW_RELEASE && fPressed){

            std::cout << network.sendTestData << std::endl;
            network.sendTestData = !network.sendTestData;
            fPressed = false;
        }
        //
        //glad_glViewport(0, 0, width, height);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

        glBegin(GL_TRIANGLES);
        glVertex2d(-0.5f, -0.5f);
        glVertex2d(0.0f, 0.5f);
        glVertex2d(0.5, -0.5f);
        glEnd();

        glfwSwapBuffers(window.window);
        //glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}