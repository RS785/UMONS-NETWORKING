cmake_minimum_required(VERSION 3.21)
project(Networking)
add_executable(Networking main.cpp Network.cpp Network.h Address.cpp Address.h Logger.cpp Logger.h
        Socket.cpp Socket.h libs/json.hpp Utils/PlayerClass.cpp Utils/PlayerClass.h Utils/Utils.h Utils/DataType.h main.cpp Window.cpp Window.h
        libs/glad.h libs/glad.c libs/khrplatform.h)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw-3.3.6)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)

include_directories(libs/glfw-3.3.6)
target_include_directories(${PROJECT_NAME} PUBLIC libs/glfw-3.3.6/include)
target_link_libraries(Networking Threads::Threads)

#[[
add_executable(Application.exe WIN32 main.cpp Network.cpp Network.h Address.cpp Address.h Logger.cpp Logger.h Socket.cpp Socket.h libs/json.hpp Utils/PlayerClass.cpp Utils/PlayerClass.h Utils/Utils.h Utils/DataType.h)]]
