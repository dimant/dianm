cmake_minimum_required(VERSION 3.16)
include(FetchContent)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
project(dainm)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)

# Add a data directory to the project
file(COPY data DESTINATION ${CMAKE_BINARY_DIR})

# These tests can use the Catch2-provided main
add_executable(dainm_tests tests/tests.cpp)
target_include_directories(dainm_tests PRIVATE include)
target_link_libraries(dainm_tests PRIVATE Catch2::Catch2WithMain)

add_executable(dainm src/main.cpp src/DataGenerator.cpp src/preprocessing.cpp)
target_include_directories(dainm PRIVATE include)
target_link_libraries(dainm PRIVATE nlohmann_json::nlohmann_json)