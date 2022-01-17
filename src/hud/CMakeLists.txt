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
        PawnCount.cpp)

add_library(HUD STATIC ${HUD_SRC})

target_include_directories(HUD PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")

#if(WIN32)
#    target_link_libraries(HUD PRIVATE sgglib GRAPHICS)
#    target_include_directories(HUD PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")
#else()
#    target_include_directories(HUD PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
##    target_link_libraries(HUD PRIVATE GRA)
#endif()

target_link_libraries(HUD PRIVATE sgglib GRAPHICS)
target_include_directories(HUD PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}/${HEADER_DIR}/sgg")

target_link_libraries(${PROJECT_NAME} PRIVATE HUD)
