target_sources(sorting_lib
    PRIVATE
        my_algorithms.cpp
    PUBLIC
        my_algorithms.hpp
)


target_include_directories(sorting_lib PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
)