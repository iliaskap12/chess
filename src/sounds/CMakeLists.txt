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

add_library(SOUND STATIC ${SOUND_SRC})

target_compile_definitions(SOUND PRIVATE _SCL_SECURE_NO_WARNINGS _ITERATOR_DEBUG_LEVEL=0)
target_include_directories(SOUND PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE SOUND)
