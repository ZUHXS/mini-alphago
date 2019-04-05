cmake_minimum_required(VERSION 3.10)
project(c_version)

set(CMAKE_CXX_STANDARD 11)

set(GLFW_H /usr/local/Cellar/glfw/3.2.1/include/GLFW)
set(GLAD_H /usr/local/include/glad)
set(KH_H /usr/local/include/KHR)
include_directories(${GLFW_H} ${GLAD_H} ${KH_H})

find_library(OPENGL OpenGL)
set(GLEW_LINK /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.dylib)
link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

set(SOURCE_FILES main.cpp chessboard.cpp chessboard.h MCTS.cpp MCTS.h glad.c)
add_executable(c_version ${SOURCE_FILES})