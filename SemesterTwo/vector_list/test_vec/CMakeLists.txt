set(SOURCES
    tests_vec.cpp
)

add_executable(tests_vec ${SOURCES})
target_link_libraries(tests_vec
    vec_list_lib
    gtest_main
    gmock_main
)

add_test(tests_vec tests_vec)
