set(
        SOUND_SRC
        CaptureSound.cpp
        ClickSound.cpp
        ClockSound.cpp
        DrawSound.cpp
        EndGameSound.cpp
        LoseSound.cpp
        MoveSound.cpp
        ResignSound.cpp
        Sound.cpp
        TimeOutSound.cpp
        WinSound.cpp
)

add_library(SOUND ${SOUND_SRC})

target_include_directories(SOUND PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE SOUND)
