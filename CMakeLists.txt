# "Why yes this is AI generated, how can you tell?"

cmake_minimum_required(VERSION 3.15)
project(Inchoatus C)

# Force strict ANSI C / C89/C90 compliance!
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(raylib QUIET)

add_executable(Inchoatus ${GAME_SOURCES})
add_subdirectory(src)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET Inchoatus PROPERTY WIN32_EXECUTABLE TRUE)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Inchoatus PRIVATE 
        -pedantic 
        -ansi
        -Werror 
        -Wall 
        -Wextra
        -Wno-comment
    )
endif()

target_include_directories(Inchoatus SYSTEM PRIVATE "${RAYLIB_DIR}")

# Platform-specific linking
if(WIN32)
    # If find_package didn't work on Windows, fallback to local path
    if(NOT raylib_FOUND)
        set(RAYLIB_DIR "C:/raylib/raylib/src" CACHE PATH "C:/raylib/raylib/src")
        target_include_directories(Inchoatus SYSTEM PRIVATE "${RAYLIB_DIR}")
        target_link_libraries(Inchoatus PRIVATE "${RAYLIB_DIR}/libraylib.a")
    else()
        target_link_libraries(Inchoatus PRIVATE raylib)
    endif()
    target_link_libraries(Inchoatus PRIVATE opengl32 gdi32 winmm)
elseif(APPLE)
    target_link_libraries(Inchoatus PRIVATE raylib "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    # LINUX
    target_link_libraries(Inchoatus PRIVATE raylib GL m pthread dl rt X11)
endif()