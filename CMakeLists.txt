cmake_minimum_required(VERSION 3.15)
project(xd_engine C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

# LTO

include(CheckIPOSupported)
check_ipo_supported(RESULT lto_supported OUTPUT error)

if(lto_supported)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# ============================================================================ #
# FOR ENGINE
# - Doesn't rely on standard libraries nor crt as it's just pure logic.

set(ENGINE_NAME "engine_core")
set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine_layout.ld")

add_library(${ENGINE_NAME} STATIC)

target_sources(${ENGINE_NAME}
    PRIVATE
    src/engine/core.c
)

target_compile_options(${ENGINE_NAME}
    PRIVATE
    -ffreestanding
)

target_link_options(${ENGINE_NAME}
    PRIVATE
    -nostdlib
)

target_link_options(${ENGINE_NAME}
    INTERFACE
    "-Wl,-T,${LINKER_SCRIPT_PATH}"
)

set_target_properties(${EXE_NAME} PROPERTIES 
    LINK_DEPENDS
    "${LINKER_SCRIPT_PATH}"
)

# ============================================================================ #
# FOR INPUT/OUTPUT
# - Current windows implementation requires standard libaries and crt.

set(IO_NAME "io_interface")
set(RAYLIB_DIR "C:/raylib/raylib/src" CACHE PATH "C:/raylib/raylib/src")

add_library(${IO_NAME} STATIC)

target_sources(${IO_NAME}
    PRIVATE
    src/io/io.c
)

target_include_directories(${IO_NAME}
    SYSTEM PRIVATE
    "${RAYLIB_DIR}"
)

# Because these libraries are different for each platform...
# NOTE: Currently only has Windows support

if(WIN32)
    target_link_libraries(${IO_NAME}
        PUBLIC
        "${RAYLIB_DIR}/libraylib.a"
        opengl32
        gdi32
        winmm
    )
endif()

# ============================================================================ #
# FOR EXECUTABLE
# - Just combines the engine, entry point, and IO interface together.

set(EXE_NAME "Inchoatus")

add_executable(${EXE_NAME})

target_sources(${EXE_NAME} PRIVATE src/main.c)

# Remove the annoying console
# NOTE: Currently only has Windows support

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(WIN32)
        set_property(TARGET ${EXE_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
    endif()
endif()

target_link_libraries(${EXE_NAME}
    PRIVATE
    ${ENGINE_NAME}
    ${IO_NAME}
)