cmake_minimum_required(VERSION 3.7...3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

project(
        chess
        VERSION 1.0
        DESCRIPTION "2 player desktop C++ chess application as a school project using Simple Game Graphics library."
        LANGUAGES CXX)


if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

    set(CMAKE_CXX_STANDARD 20)
    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDEs
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Testing only available if this is the main app
    # Note this needs to be done in the main CMakeLists
    # since it calls enable_testing, which must be in the
    # main CMakeLists.
    include(CTest)

    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if (Doxygen_FOUND)
        set(DOCS_DIR docs-doxygen)
        add_subdirectory(${DOCS_DIR})
    else ()
        message(STATUS "Doxygen not found, not building docs")
    endif ()
endif ()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if (${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif ()

set(CMAKE_CURRENT_SOURCE_DIR src)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

set(
        GAME_LIBS
        GAME
        SOUND
        GRAPHICS
        HUD
)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}")

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
        AND BUILD_TESTING)
    #    add_subdirectory(tests)
    enable_testing()
endif ()

