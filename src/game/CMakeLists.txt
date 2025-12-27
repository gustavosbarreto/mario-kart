# Game module

add_executable(game
    Camera.cpp
    main.cpp
    Game.cpp
    Opponent.cpp
    Player.cpp
)

target_include_directories(game
    PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(game
    PRIVATE
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
)

target_link_libraries(game
    PRIVATE
        common
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
