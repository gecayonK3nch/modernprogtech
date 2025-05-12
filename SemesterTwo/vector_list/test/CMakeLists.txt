set(SOURCES
    tests.cpp
)

add_executable(tests ${SOURCES})
target_link_libraries(tests
    vec_list_lib
    gtest_main
    gmock_main
)

add_test(tests tests)
