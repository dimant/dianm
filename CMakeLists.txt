cmake_minimum_required(VERSION 3.10)
project(dainm)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(include)

add_executable(dainm src/main.cpp src/DataGenerator.cpp)