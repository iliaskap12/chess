set(
        GAME_SRC
        Bishop.cpp
        Checkboard.cpp
        Clock.cpp
        Game.cpp
        King.cpp
        Knight.cpp
        Pawn.cpp
        Player.cpp
        Queen.cpp
        Rook.cpp
        Soldier.cpp
        Square.cpp
        PawnColor.cpp
)

add_library(GAME STATIC ${GAME_SRC})

#if(WIN32)
#    target_link_libraries(GAME PRIVATE sgglib)
#    target_include_directories(GAME PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")
#else()
#    target_include_directories(GRAPHICS PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
#    target_link_libraries(GRAPHICS PRIVATE sgg)
#endif()

target_link_libraries(GAME PRIVATE sgglib)
target_include_directories(GAME PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")
target_link_libraries(${PROJECT_NAME} PRIVATE GAME)
