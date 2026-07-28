cmake_minimum_required(VERSION 3.10)

project(traveling_salesman VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    methods.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})