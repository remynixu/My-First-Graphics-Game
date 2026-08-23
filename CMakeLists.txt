cmake_minimum_required(VERSION 3.15)
project(Inchoatus C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(Inchoatus ${GAME_SOURCES})

add_subdirectory(src)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET Inchoatus PROPERTY WIN32_EXECUTABLE TRUE)
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Inchoatus PRIVATE 
        -pedantic 
        -Werror 
        -Wall 
        -Wextra
        -Wno-comment
    )
endif()

# Replace this fallback path if you local Raylib installation is moved.
set(RAYLIB_DIR "C:/raylib/raylib/src" CACHE PATH "Path to raylib source/build directory")

target_include_directories(Inchoatus SYSTEM PRIVATE "${RAYLIB_DIR}")

# Platform-specific linking...
if(WIN32)
    target_link_libraries(Inchoatus PRIVATE 
        "${RAYLIB_DIR}/libraylib.a"
        opengl32 
        gdi32 
        winmm
    )
elseif(APPLE)
    target_link_libraries(Inchoatus PRIVATE raylib "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
    target_link_libraries(Inchoatus PRIVATE raylib GL m pthread dl rt X11)
endif()