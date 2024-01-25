# Project main CMake file

cmake_minimum_required(VERSION 3.2)

project(
    locator
    DESCRIPTION ""
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(apps)
add_subdirectory(src)
add_subdirectory(tests)

# Enable FetchContent module
include(FetchContent)

# Adds GoogleTest library to the project
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

# Adds nlohmann/json library to the project
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# Adds gabime/spdlog library to the project
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.11.0)
FetchContent_MakeAvailable(spdlog)

# Enable testing functionality
enable_testing()

