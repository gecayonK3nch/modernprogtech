cmake_minimum_required(VERSION 3.2...3.27.5)

project(multiproject)
enable_testing()

add_subdirectory(lib/googletest)
add_subdirectory(sorting)
add_subdirectory(menu)

set(CMAKE_SUPPRESS_REGENERATION true)