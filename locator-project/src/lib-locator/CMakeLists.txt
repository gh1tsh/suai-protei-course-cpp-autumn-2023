# This is CMake file for locator library

project(lib-locator)

add_library(
    liblocator STATIC
    lib_locator.hpp lib_locator.cpp
    ../zone/zone.hpp ../zone/zone.cpp
    ../subscriber/subscriber.hpp ../subscriber/subscriber.cpp
    ../zone/zone_trigger.hpp ../zone/zone_trigger.cpp
    ../subscriber/proximity_trigger.hpp ../subscriber/proximity_trigger.cpp)

target_include_directories(liblocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    liblocator
    PUBLIC spdlog::spdlog_header_only
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC libzone
    PUBLIC libsubscriber)

