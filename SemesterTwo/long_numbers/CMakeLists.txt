cmake_minimum_required(VERSION 3.31)

project(long_numbers)

add_library(long_numb_lib)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)

target_compile_features(long_numb_lib PRIVATE cxx_std_17)
