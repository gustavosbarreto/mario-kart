# TrackEditor module

add_executable(editor
    main.cpp
    TrackEditor.cpp
    ../game/Camera.cpp
)

target_include_directories(editor
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_CURRENT_SOURCE_DIR}/../game
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(editor
    PRIVATE
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
)

target_link_libraries(editor
    PRIVATE
        common
)
