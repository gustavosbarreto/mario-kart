# Common library (Allegro-compat + shared engine)

# Dependencies via pkg-config (Linux/macOS) or find_package (Windows/vcpkg)
find_package(PkgConfig QUIET)

if(PkgConfig_FOUND)
  # Linux/macOS: use pkg-config
  pkg_check_modules(SDL2 REQUIRED sdl2)
  pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
  pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
else()
  # Windows: use find_package with vcpkg
  find_package(SDL2 REQUIRED CONFIG)
  find_package(SDL2_ttf REQUIRED CONFIG)
  find_package(SDL2_image REQUIRED CONFIG)
endif()

add_library(common STATIC
    allegro.cpp
    AllegroSystem.cpp
    AllegroScreen.cpp
    AllegroKeyboard.cpp
    SuperMode7.cpp
    ObjectSize.cpp
    Vector.cpp
    Track.cpp
)

target_include_directories(common
    PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(common
    PRIVATE
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_IMAGE_LIBRARY_DIRS}
)

target_link_libraries(common
    PRIVATE
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
