cmake_minimum_required(VERSION 3.1.0)
project(CiExample VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(app)
