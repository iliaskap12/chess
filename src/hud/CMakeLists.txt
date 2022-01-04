set(
        HUD_SRC
        CheckIndicator.cpp
        Draw.cpp
        EndgameIndicator.cpp
        HUD.cpp
        Indicator.cpp
        Moveboard.cpp
        MoveTakeback.cpp
        Offer.cpp
        Resignment.cpp
        TimeIncrement.cpp
        Timer.cpp
        TurnIndicator.cpp
)

add_library(HUD ${HUD_SRC})

target_include_directories(HUD PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE HUD)
