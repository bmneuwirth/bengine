cmake_minimum_required(VERSION 3.25)
project(cubelands)

set(CMAKE_CXX_STANDARD 17)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

add_executable(cubelands src/main.cpp src/game.cpp src/game.h src/shader.cpp src/shader.h include/stb_image.h
        src/texture.cpp
        src/texture.h
        src/texture.h
        src/object.cpp
        src/object.h
        src/object.h src/camera.cpp src/camera.h src/camera.h src/camera.cpp)
target_link_libraries(cubelands ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} GLEW::GLEW glm::glm)
