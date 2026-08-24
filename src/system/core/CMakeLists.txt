target_sources(Inchoatus PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/renderer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/screen.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tile.c"
)

add_subdirectory(env)
add_subdirectory(primitives)
