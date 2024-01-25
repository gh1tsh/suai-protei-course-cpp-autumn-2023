# This is CMake file for subscriber class project interface

project(libsubscriber)

add_library(libsubscriber INTERFACE)

target_include_directories(libsubscriber INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    libsubscriber
    INTERFACE spdlog::spdlog_header_only)
