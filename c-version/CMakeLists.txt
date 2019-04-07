cmake_minimum_required(VERSION 3.10)
project(c_version)

set(CMAKE_CXX_STANDARD 11)


include_directories(/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7)
set(CMAKE_LIBRARY_PATH "/System/Library/Frameworks/Python.framework/Versions/2.7/lib")
link_libraries(python)


set(SOURCE_FILES main.cpp chessboard.cpp chessboard.h MCTS.cpp MCTS.h)
add_executable(c_version ${SOURCE_FILES})