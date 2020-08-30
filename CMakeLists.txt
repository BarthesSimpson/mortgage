cmake_minimum_required(VERSION 3.17)
project(mortgage)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(lib)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
add_subdirectory(lib/toml11)