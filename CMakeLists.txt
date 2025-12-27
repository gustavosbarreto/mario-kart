cmake_minimum_required(VERSION 3.16)

project(mario_kart LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Common library in subdirectory
add_subdirectory(src/common)

# Subdirectories for executables
add_subdirectory(src/game)
add_subdirectory(src/editor)

# Convenience targets
add_custom_target(run-game
    COMMAND $<TARGET_FILE:game>
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(run-editor
    COMMAND $<TARGET_FILE:editor>
    DEPENDS editor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Copy Data directory to build folder for convenience
add_custom_target(copy-data ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMENT "Copying Data directory to build folder"
)

# Install rules for distribution
install(TARGETS game editor
    RUNTIME DESTINATION .
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data
    DESTINATION .
    PATTERN ".DS_Store" EXCLUDE
)

# Install runtime dependencies (DLLs on Windows)
if(WIN32)
    install(CODE [[
        file(GET_RUNTIME_DEPENDENCIES
            EXECUTABLES
                "${CMAKE_INSTALL_PREFIX}/game.exe"
                "${CMAKE_INSTALL_PREFIX}/editor.exe"
            RESOLVED_DEPENDENCIES_VAR _r_deps
            UNRESOLVED_DEPENDENCIES_VAR _u_deps
            DIRECTORIES
                "${CMAKE_BINARY_DIR}"
                "${CMAKE_PREFIX_PATH}/bin"
        )
        foreach(_file ${_r_deps})
            get_filename_component(_filename "${_file}" NAME_WE)
            get_filename_component(_fullname "${_file}" NAME)
            # Only copy SDL2 and its direct dependencies (libpng, zlib, freetype)
            if(_filename MATCHES "^SDL2" OR _filename MATCHES "^(libpng|zlib|freetype)")
                file(INSTALL
                    DESTINATION "${CMAKE_INSTALL_PREFIX}"
                    TYPE SHARED_LIBRARY
                    FOLLOW_SYMLINK_CHAIN
                    FILES "${_file}"
                )
            endif()
        endforeach()
    ]])
endif()

# Print summary
message(STATUS "SDL2 include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf include: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_image include: ${SDL2_IMAGE_INCLUDE_DIRS}")
