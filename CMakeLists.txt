cmake_minimum_required(VERSION 3.15)
project(xd_engine C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(ENGINE_NAME "engine_core")
set(IO_NAME "io_interface")
set(EXE_NAME "Inchoatus")

# ============================================================================ #
# FOR DEBUG/RELEASE
# :<

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # LTO (Link-Time Optimization)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT error)
    if(lto_supported)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
    endif()
    # More optimizations?
    add_compile_options(
        -O2
    )
else()
    add_compile_options(
        -O0
    )
endif()

# ============================================================================ #
# FOR ENGINE
# - Doesn't rely on standard libraries nor crt as it's just pure logic.

add_library(${ENGINE_NAME} STATIC)

add_subdirectory("src")

# ============================================================================ #
# FOR INPUT/OUTPUT
# - Current windows implementation requires standard libaries and crt.

add_library(${IO_NAME} STATIC)

add_subdirectory("src/io")

# ============================================================================ #
# FOR EXECUTABLE
# - Just combines the engine, entry point, and IO interface together.

add_executable(${EXE_NAME} WIN32
    src/main.c
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    ${ENGINE_NAME}
    ${IO_NAME}
)