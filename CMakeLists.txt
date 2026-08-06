cmake_minimum_required(VERSION 3.15)
project(Arundel C)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(game ${GAME_SOURCES})

set_target_properties(game PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS OFF
)

target_compile_options(game PRIVATE 
    -std=c89 
    -pedantic 
    -Werror 
    -Wall 
    -Wno-comment
    -Wno-c++-compat
)

target_include_directories(game SYSTEM PRIVATE "C:/raylib/raylib/src")

target_link_libraries(game PRIVATE 
    "C:/raylib/raylib/src/libraylib.a"
    opengl32 
    gdi32 
    winmm
)
