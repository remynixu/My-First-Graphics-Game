if(NOT DEFINED IO_NAME)
    message(FATAL_ERROR "How dare you not set IO_NAME?")
endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/sources.cmake")

if(NOT DEFINED IO_SOURCE_FILES)
    message(FATAL_ERROR "Huh? Where's our source files? D:")
endif()

target_sources(${IO_NAME}
    PRIVATE
    ${IO_SOURCE_FILES}
)

set(RAYLIB_DIR "C:/raylib/raylib/src" CACHE PATH "C:/raylib/raylib/src")

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