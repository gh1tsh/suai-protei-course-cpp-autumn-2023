
project(locator-check)

add_executable(prog_locator main.cpp)
target_link_libraries(
    prog_locator
    PRIVATE liblocator)
