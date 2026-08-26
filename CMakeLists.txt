# "Why yes this is AI generated, how can you tell?"

cmake_minimum_required(VERSION 3.15)
project(Inchoatus C)

find_package(raylib QUIET)

add_executable(Inchoatus)
add_subdirectory(src)

set_target_properties(Inchoatus PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_property(TARGET Inchoatus PROPERTY WIN32_EXECUTABLE TRUE)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(Inchoatus PRIVATE 
            -O2
            -flto
        )
        target_link_options(Inchoatus PRIVATE
            -static
            -flto
        )
    endif()
endif()

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Inchoatus PRIVATE 
        -pedantic 
        -Werror 
        -Wall 
        -Wextra
    )
endif()

if(WIN32)
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