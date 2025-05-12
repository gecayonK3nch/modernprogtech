target_sources(vec_list_lib
    PRIVATE
        src/vector.cpp
        src/doubly_linked_list.cpp
)

target_include_directories(vec_list_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
