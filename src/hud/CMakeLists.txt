set(
        HUD_SRC
        src/CheckIndicator.cpp
        src/Draw.cpp
        src/EndgameIndicator.cpp
        src/HUD.cpp
        src/Indicator.cpp
        src/Moveboard.cpp
        src/MoveTakeback.cpp
        src/Offer.cpp
        src/Resignment.cpp
        src/TimeIncrement.cpp
        src/Timer.cpp
        src/TurnIndicator.cpp
        src/PawnCount.cpp)

add_library(HUD ${HUD_SRC})

target_include_directories(
        HUD
        PRIVATE
        "${SRC_DIR}/hud"
        "${SRC_DIR}/hud/hud"
        "${SRC_DIR}/graphics"
)

target_link_libraries(${PROJECT_NAME} PRIVATE HUD)
