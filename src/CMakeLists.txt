if(NOT DEFINED ENGINE_NAME)
    message(FATAL_ERROR "How dare you not set ENGINE_NAME? Grr...")
endif()

if(NOT DEFINED EXE_NAME)
    message(FATAL_ERROR "How dare you not set EXE_NAME? Hmff...")
endif()

# Hmm... seems like it'll always fail because ENGINE_ASSET_OBJECTS will always
# be empty before the main script starts.

include("${CMAKE_CURRENT_SOURCE_DIR}/engine/sources.cmake")

if(NOT DEFINED ENGINE_SOURCE_FILES)
    message(FATAL_ERROR "Huh? Where's our source files? D:")
endif()

target_sources(${ENGINE_NAME}
    PRIVATE
    ${ENGINE_SOURCE_FILES}
)

target_compile_options(${ENGINE_NAME}
    PRIVATE
    -ffreestanding
)