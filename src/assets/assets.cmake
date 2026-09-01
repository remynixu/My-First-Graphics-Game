# NOTE: This file is meant to be *include()*'d, or else the directories will
# break...

set(ASSETS_DIR "${CMAKE_CURRENT_LIST_DIR}")

set(ENTITY_DIR "${ASSETS_DIR}/textures/entity")
set(TILE_DIR "${ASSETS_DIR}/textures/tile")

# Functions to safely convert raw assets to object files
# AI GENERATED??!?!?!?!

function(pngtoobj_asset ASSET_PATH)
    # 1. Isolate the asset name (e.g., /path/to/player -> player)
    get_filename_component(ASSET_NAME "${ASSET_PATH}" NAME)
    
    # 2. Define your clear, separate file paths
    set(INPUT_PNG "${ASSET_PATH}.png")
    set(INTERMEDIATE_XD "${CMAKE_CURRENT_BINARY_DIR}/${ASSET_NAME}.xd")
    set(FINAL_OBJ "${CMAKE_CURRENT_BINARY_DIR}/${ASSET_NAME}.obj")

    set(PYTHON_COMMAND "${CMAKE_CURRENT_LIST_DIR}/assets_handler.py")

    # --- STEP 1: PNG to XD ---
    add_custom_command(
        OUTPUT "${INTERMEDIATE_XD}"
        COMMAND python ${PYTHON_COMMAND} "${INPUT_PNG}" "${INTERMEDIATE_XD}"
        DEPENDS "${INPUT_PNG}"
        COMMENT "Converting to .xd asset: ${INPUT_PNG}"
    )

    # --- STEP 2: XD to OBJ ---
    add_custom_command(
        OUTPUT "${FINAL_OBJ}"
        COMMAND ${CMAKE_LINKER} -r -b binary "${INTERMEDIATE_XD}" -o "${FINAL_OBJ}"
        DEPENDS "${INTERMEDIATE_XD}"
        COMMENT "Converting to .obj asset: ${INTERMEDIATE_XD}"
    )

    # --- STEP 3: Pass the final file up ---
    # We update the global list with ONLY the final .obj file.
    # The intermediate .xd file stays safely hidden.
    set(ENGINE_ASSET_OBJECTS ${ENGINE_ASSET_OBJECTS} "${FINAL_OBJ}" PARENT_SCOPE)
endfunction()