set(
        SOUND_SRC
        src/CaptureSound.cpp
        src/ClickSound.cpp
        src/ClockSound.cpp
        src/DrawSound.cpp
        src/EndGameSound.cpp
        src/LoseSound.cpp
        src/MoveSound.cpp
        src/ResignSound.cpp
        src/Sound.cpp
        src/TimeOutSound.cpp
        src/WinSound.cpp
        src/CheckSound.cpp
)

add_library(SOUND ${SOUND_SRC})

target_include_directories(
        SOUND
        PRIVATE
        "${SRC_DIR}/sounds/sounds"
        "${SRC_DIR}/sounds"
        "${SRC_DIR}/util"

)
target_link_libraries(${PROJECT_NAME} PRIVATE SOUND)
