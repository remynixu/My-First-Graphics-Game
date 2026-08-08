cmake_minimum_required(VERSION 3.15)
project(Arundel C)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(Arundel ${GAME_SOURCES})

#if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
#    set_property(TARGET Arundel PROPERTY WIN32_EXECUTABLE TRUE)
#endif()

set_target_properties(Arundel PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS OFF
)

target_compile_options(Arundel PRIVATE 
    -std=c89 
    -pedantic 
    -Werror 
    -Wall 
    -Wno-comment
    -Wno-c++-compat
)

target_include_directories(Arundel SYSTEM PRIVATE "C:/raylib/raylib/src")

target_link_libraries(Arundel PRIVATE 
    "C:/raylib/raylib/src/libraylib.a"
    opengl32 
    gdi32 
    winmm
)
