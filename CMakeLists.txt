cmake_minimum_required(VERSION 3.15)
project(xd_engine C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(ENGINE_NAME "engine_core")
set(IO_NAME "io_interface")
set(EXE_NAME "Inchoatus")

# ============================================================================ #
# FOR DEBUG/RELEASE
# :<

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

    # Remove the annoying console
    # NOTE: Currently only has Windows support

    if(WIN32)
        set_property(TARGET ${EXE_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
    endif()

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
# FOR ASSETS
# - Will be automated with Python soon! :D

# Function to safely convert raw assets to Windows PE-COFF object files

function(embed_asset ASSET_PATH OUTPUT_OBJ_NAME)
    set(OUT_OBJ "${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_OBJ_NAME}")
    add_custom_command(
        OUTPUT "${OUT_OBJ}"
        COMMAND ${CMAKE_LINKER} -r -b binary "${ASSET_PATH}" -o "${OUT_OBJ}"
        DEPENDS "${ASSET_PATH}"
        COMMENT "Compiling asset: ${ASSET_PATH}"
    )
    # Expose the compiled object globally so we can link it
    set(ENGINE_ASSET_OBJECTS ${ENGINE_ASSET_OBJECTS} "${OUT_OBJ}" PARENT_SCOPE)
endfunction()

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/assets")

# Entities go here...

embed_asset("${ASSETS_DIR}/textures/entity/arundel.png"   "arundel.png.o")
embed_asset("${ASSETS_DIR}/textures/entity/null.png"      "entity_null.png.o")
embed_asset("${ASSETS_DIR}/textures/entity/rock.png"      "rock.png.o")

# Then tiles go here.

embed_asset("${ASSETS_DIR}/textures/tile/grass.png"       "grass.png.o")
embed_asset("${ASSETS_DIR}/textures/tile/null.png"        "tile_null.png.o")

# ============================================================================ #
# FOR ENGINE
# - Doesn't rely on standard libraries nor crt as it's just pure logic.

set(LINKER_SCRIPT_PATH_1 "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/layout.ld")
set(LINKER_SCRIPT_PATH_2 "${CMAKE_CURRENT_SOURCE_DIR}/src/assets/layout.ld")

add_library(${ENGINE_NAME} STATIC)

add_subdirectory("src/engine")

target_sources(${ENGINE_NAME}
    PRIVATE
    ${ENGINE_ASSET_OBJECTS}
)

target_compile_options(${ENGINE_NAME}
    PRIVATE
    -ffreestanding
)

target_link_options(${ENGINE_NAME}
    INTERFACE
    "-Wl,-dT,${LINKER_SCRIPT_PATH_1}"
    "-Wl,-dT,${LINKER_SCRIPT_PATH_2}"
)

# ============================================================================ #
# FOR INPUT/OUTPUT
# - Current windows implementation requires standard libaries and crt.

set(RAYLIB_DIR "C:/raylib/raylib/src" CACHE PATH "C:/raylib/raylib/src")

add_library(${IO_NAME} STATIC)

add_subdirectory("src/io")

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

add_executable(${EXE_NAME})

target_sources(${EXE_NAME} PRIVATE src/main.c)

set_target_properties(${EXE_NAME} PROPERTIES 
    LINK_DEPENDS
    "${LINKER_SCRIPT_PATH_1};${LINKER_SCRIPT_PATH_2}"
)

target_link_libraries(${EXE_NAME}
    PRIVATE
    ${ENGINE_NAME}
    ${IO_NAME}
)