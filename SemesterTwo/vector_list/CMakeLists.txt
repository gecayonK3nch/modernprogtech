set(gtest_force_shared_crt ON CACHE BOOL "Use shared runtime library" FORCE)

add_executable(tests tests.cpp doubly_linked_list.cpp vector.cpp)

add_subdirectory(lib/googletest)

target_link_libraries(tests
    gtest
    ${CONTAINERS_LIB}
)

add_test(tests tests)
