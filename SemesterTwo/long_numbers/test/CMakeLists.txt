set(SOURCES
    test.cpp
)

add_executable(test ${SOURCES})

# set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib" ${CMAKE_PREFIX_PATH})
# find_package(GoogleTest REQUIRED)

target_link_libraries(test
    gtest_main
    long_numb_lib
)

add_test(test test)
