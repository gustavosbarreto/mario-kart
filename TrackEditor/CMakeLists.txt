# TrackEditor module

add_executable(editor
    main.cpp
    TrackEditor.cpp
    ../Game/Camera.cpp
)

target_include_directories(editor
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Common
        ${CMAKE_CURRENT_SOURCE_DIR}/../Game
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
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
