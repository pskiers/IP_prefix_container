cmake_minimum_required(VERSION 3.1.0)
project(CiExample VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include_directories(lib)

enable_testing()

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(app)
