target_sources(long_numb_lib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/long_number.cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/long_number.hpp
)
target_include_directories(long_numb_lib PUBLIC
         "${PROJECT_SOURCE_DIR}/src"
)