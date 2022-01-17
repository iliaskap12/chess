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
        Point.cpp
        Rectangle.cpp
)

add_library(GRAPHICS STATIC ${GRAPHICS_SRC})

#if(WIN32)
#    target_link_libraries(GRAPHICS PRIVATE HUD sgglib)
#    target_include_directories(GRAPHICS PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")
#else()
#    target_include_directories(GRAPHICS PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
#    target_link_libraries(GRAPHICS PRIVATE HUD)
#endif()

target_link_libraries(GRAPHICS PRIVATE HUD sgglib)
target_include_directories(GRAPHICS PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")
target_link_libraries(${PROJECT_NAME} PRIVATE GRAPHICS)
