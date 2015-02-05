cmake_minimum_required(VERSION 2.8.4)
project(mod1)

include_directories(includes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/Volumes/Data/nfs/zfs-student-3/users/2013/msagodir/.brew/Cellar/glfw3/3.0.4/include -I/.includes -I/nfs/zfs-student-3/users/2013/msagodir/.brew/include ")

set(SOURCE_FILES
    srcs/Main.cpp
    srcs/Model.cpp
    srcs/GLFWManager.cpp
    srcs/Shader.cpp
    srcs/TimeManager.cpp
    srcs/Camera.cpp
    srcs/InputManager.cpp)

add_executable(mod1 ${SOURCE_FILES})

