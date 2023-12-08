cmake_minimum_required(VERSION 3.26)

# Project name and language
project(locator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main target
add_executable(locator main.cpp
        zone.cpp
        zone.h
        subscriber.cpp
        subscriber.h
        locator.cpp
        locator.h
        zone_trigger.cpp
        zone_trigger.h
        proximity_trigger.cpp
        proximity_trigger.h)
target_link_libraries(
        locator
        PUBLIC spdlog::spdlog_header_only
        PUBLIC nlohmann_json::nlohmann_json
)

# Enable FetchContent module
include(FetchContent)

# Adds GoogleTest library to the project
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Adds nlohmann/json library to the project
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Adds gabime/spdlog library to the project
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)


# Test target
add_executable(unit_tests unit_tests.cpp
        locator.cpp
        locator.h
        zone.cpp
        zone.h
        subscriber.cpp
        subscriber.h
        zone_trigger.cpp
        zone_trigger.h
        proximity_trigger.cpp
        proximity_trigger.h
)
target_link_libraries(
        unit_tests
        PUBLIC gtest_main
        PUBLIC spdlog::spdlog_header_only
        PUBLIC nlohmann_json::nlohmann_json
)

# Enable testing functionality
enable_testing()