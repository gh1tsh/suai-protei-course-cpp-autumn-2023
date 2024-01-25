# This is CMake file for zone class project interface

project(libzone)

add_library(libzone INTERFACE)

target_include_directories(libzone INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    libzone
    INTERFACE spdlog::spdlog_header_only)
