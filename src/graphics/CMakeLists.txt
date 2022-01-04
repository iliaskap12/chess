set(
        GRAPHICS_SRC
        InGameMenu.cpp
        MainMenu.cpp
        Menu.cpp
        MenuOption.cpp
        MenuScreen.cpp
        OpeningScreen.cpp
        PlayingScreen.cpp
        Screen.cpp
)

add_library(GRAPHICS ${GRAPHICS_SRC})

target_include_directories(GRAPHICS PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE GRAPHICS)
