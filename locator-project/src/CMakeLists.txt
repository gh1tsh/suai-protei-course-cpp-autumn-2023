# This CMake file manages the build of the source files, which are then
# used in applications and tests.

project(project-srcs)

add_subdirectory(lib-locator)
add_subdirectory(subscriber)
add_subdirectory(zone)
add_subdirectory(proto-gen)
