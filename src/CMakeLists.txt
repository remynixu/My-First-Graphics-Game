if(NOT DEFINED ENGINE_NAME)
    message(FATAL_ERROR "How dare you not set ENGINE_NAME? Grr...")
endif()

if(NOT DEFINED EXE_NAME)
    message(FATAL_ERROR "How dare you not set EXE_NAME? Hmff...")
endif()

# Hmm... seems like it'll always fail because ENGINE_ASSET_OBJECTS will always
# be empty before the main script starts.

# if(NOT DEFINED ENGINE_ASSET_OBJECTS)
#    message(FATAL_ERROR "How dare you not set ENGINE_ASSET_OBJECTS? Hmph.")
# endif()

include("${CMAKE_CURRENT_SOURCE_DIR}/engine/sources.cmake")

if(NOT DEFINED ENGINE_SOURCE_FILES)
    message(FATAL_ERROR "Huh? Where's our source files? D:")
endif()

target_sources(${ENGINE_NAME}
    PRIVATE
    ${ENGINE_SOURCE_FILES}
    ${ENGINE_ASSET_OBJECTS}
)

target_compile_options(${ENGINE_NAME}
    PRIVATE
    -ffreestanding
)

include("${CMAKE_CURRENT_SOURCE_DIR}/linkers.cmake")

target_link_options(${ENGINE_NAME}
    INTERFACE
    "-Wl,-dT,${LINKER_SCRIPT_PATH_1}"
    "-Wl,-dT,${LINKER_SCRIPT_PATH_2}"
)