cmake_minimum_required(VERSION 3.25)
project(cubelands)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(cubelands main.cpp game.cpp game.h shader.cpp shader.h stb_image.h
        texture.cpp
        texture.h
        texture.h
        object.cpp
        object.h
        object.h)
target_link_libraries(cubelands ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} GLEW::GLEW)
