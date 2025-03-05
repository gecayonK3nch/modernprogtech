add_executable(test_sorting test_sorting.cpp)

target_link_libraries(test_sorting
    gtest_main
    gmock_main
    sorting_lib
)

add_test(test_sorting test_sorting)
