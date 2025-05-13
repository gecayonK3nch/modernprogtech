project(vector_list)
cmake_minimum_required(VERSION 3.10)

set(gtest_force_shared_crt ON CACHE BOOL "Use shared runtime library" FORCE)

add_library(vec_list_lib "")

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(src)
add_subdirectory(test_vec)
add_subdirectory(test_list)
