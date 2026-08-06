cmake_minimum_required(VERSION 3.10)

project(traveling_salesman VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/methods.cpp
    src/window.cpp
    src/rendering_shapes.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

#Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})