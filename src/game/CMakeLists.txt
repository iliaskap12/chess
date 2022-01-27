set(
        GAME_SRC
        src/Bishop.cpp
        src/Checkboard.cpp
        src/Clock.cpp
        src/Game.cpp
        src/King.cpp
        src/Knight.cpp
        src/Pawn.cpp
        src/Player.cpp
        src/Queen.cpp
        src/Rook.cpp
        src/Soldier.cpp
        src/Square.cpp
        src/PawnColor.cpp
)

add_library(GAME ${GAME_SRC})

target_include_directories(
        GAME
        PRIVATE
        "${SRC_DIR}"
        "${SRC_DIR}/game"
        "${SRC_DIR}/game/game"
        "${SRC_DIR}/graphics"
        "${SRC_DIR}/util"
        "${SRC_DIR}/hud"
        "${SRC_DIR}/sounds"
)

target_link_libraries(GAME PRIVATE SOUND)
target_link_libraries(${PROJECT_NAME} PRIVATE GAME)
