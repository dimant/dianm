cmake_minimum_required(VERSION 3.16)
include(FetchContent)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(dainm)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# Add a data directory to the project
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

add_executable(dainm src/main.cpp src/DataGenerator.cpp src/preprocessing.cpp)
target_include_directories(dainm PRIVATE include)
target_link_libraries(dainm PRIVATE nlohmann_json::nlohmann_json)