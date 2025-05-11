set(SOURCES
    test.cpp
)
add_executable(test ${SOURCES})
target_link_libraries(test
    gtest_main
    long_numb_lib
)
add_test(test test)

set(SOURCES
    test_long_number.cpp
)
add_executable(test_long_number ${SOURCES})
target_link_libraries(test_long_number
    gtest_main
    long_numb_lib
)
add_test(test_long_number test)