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
)

add_library(GAME ${GAME_SRC})

target_include_directories(GAME PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE GAME)
