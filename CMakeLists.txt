cmake_minimum_required(VERSION 3.1.0)
project(Prefix_Container VERSION 0.1.0)

set (CMAKE_C_STANDARD 11)

include_directories(lib)

enable_testing()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(app)
