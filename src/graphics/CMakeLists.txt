set(
        GRAPHICS_SRC
        src/InGameMenu.cpp
        src/MainMenu.cpp
        src/Menu.cpp
        src/MenuOption.cpp
        src/MenuScreen.cpp
        src/OpeningScreen.cpp
        src/PlayingScreen.cpp
        src/Screen.cpp
        src/Point.cpp
        src/Rectangle.cpp
)

add_library(GRAPHICS ${GRAPHICS_SRC})
target_include_directories(
        GRAPHICS
        PRIVATE
        "${SRC_DIR}"
        "${SRC_DIR}/graphics"
        "${SRC_DIR}/graphics/graphics"
        "${SRC_DIR}/game"
        "${SRC_DIR}/util"
        "${SRC_DIR}/hud"
        "${SRC_DIR}/sounds"
)

message("${SRC_DIR}/hud")

target_link_libraries(GRAPHICS PRIVATE HUD UTIL)
target_link_libraries(${PROJECT_NAME} PRIVATE GRAPHICS)
