# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if (${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif ()

#================================================
# CMAKE BUILD
# WINDOW BUILD CURRENTLY
#================================================
message("CMAKE_BUILD_TYPE >>> "  ${CMAKE_BUILD_TYPE})
#convert checks for debug / release
#string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    set(CMAKE_BUILD_TYPE Debug)
    message("DEBUG mode ==============================================================")
elseif(CMAKE_BUILD_TYPE STREQUAL "release")
    set(CMAKE_BUILD_TYPE Release)
    message("RELEASE mode ==============================================================")
else()
    set(CMAKE_BUILD_TYPE Debug)
    message("NONE mode ==============================================================")
endif()

message("Start of CMakeLists.txt...")
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
set(BUILD_SHARED_LIBS OFF)
#================================================
# CONFIGS
#================================================
# deal with add ons and checks tests
# GLEW through glew wrapper provided by Perlmint https://github.com/Perlmint/glew-cmake
set(ENABLE_GLEW ON)
# GLM https://github.com/g-truc/glm.git
set(ENABLE_GLM ON)
# WINDOW / INPUT / CPU RENDER
set(ENABLE_SDL ON)
# FONT
set(ENABLE_FREETYPE ON) #needed for sdl image
# SOUND / AUDIO
set(ENABLE_SDL_MIXER ON)

#================================================
# GIT PACKAGE VERSION
#================================================
set(FREETYPE_GIT_TAG master) # GITHUB RELEASE TAG
set(GLEW_GIT_TAG master)
set(GLM_GIT_TAG master)
set(SDL_GIT_TAG main) # SDL GITHUB RELEASE TAG
set(SDL_MIXER_GIT_TAG master) # SDL GITHUB RELEASE TAG
#================================================
#================================================
# CONFIGS
#================================================
#et(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
message("CMAKE_SYSTEM_NAME == " ${CMAKE_SYSTEM_NAME})
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #target_compile_options(myApp PRIVATE /W4)
    #message("WINDOWS")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #target_compile_options(myApp PRIVATE -Wall -Wextra -Wpedantic)
    #message("Linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # other macOS-specific flags for Clang
    #message("Darwin")
endif()

message("CMAKE_CURRENT_SOURCE_DIR  >>>  " ../sgg2)
message("CMAKE_CURRENT_BINARY_DIR  >>>  " ${CMAKE_CURRENT_BINARY_DIR})

# Must set output build directory. By default is none. User must configure it manuallly
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}") # workspace/build/Debug
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# folders, files, libs
set(CPP_INCLUDE_DIRS "")
set(CPP_HEADER_FILES "")
set(CPP_SOURCE_FILES "")
set(CPP_LIBS "")

if (ENABLE_GLM)
    # base on environment system path variable set.
    if (NOT glm_FOUND) # If there's none, fetch and build glm
        include(FetchContent)
        FetchContent_Declare(
                glm
                GIT_REPOSITORY https://github.com/g-truc/glm.git
                GIT_TAG ${GLM_GIT_TAG}
        )
        FetchContent_GetProperties(glm)
        if (NOT glm_POPULATED)
            FetchContent_Populate(glm)

            # build GLM
            list(APPEND CPP_INCLUDE_DIRS ${glm_SOURCE_DIR}/include)
            if(NOT EXISTS ${glm_SOURCE_DIR})
                file(MAKE_DIRECTORY ${glm_SOURCE_DIR})
            endif()
            if(NOT EXISTS ${glm_BINARY_DIR})
                file(MAKE_DIRECTORY ${glm_BINARY_DIR})
            endif()
            add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR} EXCLUDE_FROM_ALL)
            list(APPEND CPP_LIBS "glm")
        endif()
    endif()
endif()
if (ENABLE_GLEW)
    # base on environment system path variable set.
    if (NOT glew_FOUND) # If there's none, fetch and build glew
        include(FetchContent)
        FetchContent_Declare(
                glew
                GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
                GIT_TAG ${GLEW_GIT_TAG}
        )
        FetchContent_GetProperties(glew)
        if (NOT glew_POPULATED)
            FetchContent_Populate(glew)

            # build GLEW
            list(APPEND CPP_INCLUDE_DIRS ${glew_SOURCE_DIR}/include)
            if(NOT EXISTS ${glew_SOURCE_DIR})
                file(MAKE_DIRECTORY ${glew_SOURCE_DIR})
            endif()
            if(NOT EXISTS ${glew_BINARY_DIR})
                file(MAKE_DIRECTORY ${glew_BINARY_DIR})
            endif()
            add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
            list(APPEND CPP_LIBS "libglew_static")
        endif()
    endif()
endif()

#================================================
# SDL
#================================================
message("[[[=== CHECKING SDL SECTION === ]]]")
if (ENABLE_SDL)
    FetchContent_Declare(
            sdl2_content
            URL https://libsdl.org/release/SDL2-2.0.20.tar.gz
    )

    FetchContent_GetProperties(sdl2_content)
    if(NOT sdl2_content_POPULATED)
        FetchContent_Populate(sdl2_content)
        if(ANDROID)
            set(SDL_SHARED ON CACHE BOOL "shared")
            set(SDL_STATIC OFF CACHE BOOL "static")
            add_subdirectory(${sdl2_content_SOURCE_DIR} ${sdl2_content_BINARY_DIR} EXCLUDE_FROM_ALL)
            add_library(SDL2::SDL2 ALIAS SDL2)
        elseif(WIN32 OR LINUX OR MACOS)
            set(SDL_SHARED OFF CACHE BOOL "shared")
            set(SDL_STATIC ON CACHE BOOL "static")
            set(SDL_STATIC_PIC ON CACHE BOOL "Static version of the library should be built with Position Independent Code")
            set(SDL_SHARED OFF)
            set(SDL_STATIC ON)
            set(SDL_STATIC_PIC ON)
            if(LINUX)
                set(SNDIO_SHARED ON CACHE BOOL "static")
                set(SNDIO_SHARED ON)
            endif()
            set(FORCE_STATIC_VCRT ON CACHE BOOL "static windows static vcrc")
            add_subdirectory(${sdl2_content_SOURCE_DIR} ${sdl2_content_BINARY_DIR} EXCLUDE_FROM_ALL)
            add_library(SDL2::SDL2 ALIAS SDL2-static)
        endif()
        add_library(SDL2 ALIAS SDL2main)

        file(GLOB INCLUDE_FILES ${sdl2_content_SOURCE_DIR}/include/*.h)
        file(GLOB BIN_INCLUDE_FILES ${sdl2_content_BINARY_DIR}/include/*.h)
        foreach(_FNAME ${BIN_INCLUDE_FILES})
            get_filename_component(_INCNAME ${_FNAME} NAME)
            list(REMOVE_ITEM INCLUDE_FILES ${sdl2_content_SOURCE_DIR}/include/${_INCNAME})
        endforeach()
        list(APPEND INCLUDE_FILES ${BIN_INCLUDE_FILES})

        if(NOT EXISTS "${sdl2_content_BINARY_DIR}/include/SDL2")
            file(MAKE_DIRECTORY "${sdl2_content_BINARY_DIR}/include/SDL2")
            file(COPY ${INCLUDE_FILES}  DESTINATION "${sdl2_content_BINARY_DIR}/include/SDL2")
        endif()
        include_directories("${sdl2_content_BINARY_DIR}/include")
        include_directories("${sdl2_content_BINARY_DIR}/sdl-src/include")
        include_directories("${sdl2_content_BINARY_DIR}/sdl2-src/include")

        if(EXISTS "${sdl2_content_SOURCE_DIR}/android-project")
            file(REMOVE_RECURSE "${sdl2_content_SOURCE_DIR}/android-project")
        endif()

        #    file(COPY CMake/Extra/sdl2-config.cmake DESTINATION ${sdl2_content_BINARY_DIR})
        set(SDL2_DIR ${sdl2_content_BINARY_DIR})
        list(APPEND SDL2_INCLUDE_DIRS "${sdl2_content_BINARY_DIR}/include/SDL2/")
        list(APPEND SDL2_INCLUDE_DIRS "${sdl2_content_BINARY_DIR}/include/")
        list(APPEND SDL2_INCLUDE_DIRS "${sdl2_content_BINARY_DIR}/sdl2-src/include")
        list(APPEND SDL2_INCLUDE_DIRS "${sdl2_content_BINARY_DIR}/sdl-src/include")
        list(APPEND SDL2_LIBRARY_DIRS "${sdl2_content_BINARY_DIR}/")
        list(APPEND SDL2_LIBRARIES SDL2::SDL2)
        list(APPEND SDL2_LIBRARIES SDL2::SDL2main)
    endif()
endif()

if (ENABLE_SDL_MIXER)
    # base on environment system path variable set.
    if (NOT sdl_mixer_FOUND) # If there's none, fetch and build sdl
        include(FetchContent)
        FetchContent_Declare(
                sdl_mixer
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
                GIT_TAG ${SDL_MIXER_GIT_TAG}
        )
        FetchContent_GetProperties(sdl_mixer)
        if (NOT sdl_mixer_POPULATED)
            FetchContent_Populate(sdl_mixer)
            #message("sdl_mixer_LIBRARY: " ${sdl_mixer_LIBRARY}) # fail but define in cmake
            #message("sdl_mixer_INCLUDE_DIR: " ${sdl_mixer_INCLUDE_DIR}) #pass
            #message("sdl_mixer_SOURCE_DIR: " ${sdl_mixer_SOURCE_DIR}) # pass
            #message("sdl_mixer_BINARY_DIR: " ${sdl_mixer_BINARY_DIR}) # pass

            set(ANDROID ON)
            set(SUPPORT_OGG ON CACHE BOOL "" FORCE)

            # build SDL2 MIXER
            list(APPEND CPP_INCLUDE_DIRS ${sdl_mixer_SOURCE_DIR}/include)
            if(NOT EXISTS ${sdl_mixer_SOURCE_DIR})
                file(MAKE_DIRECTORY ${sdl_mixer_SOURCE_DIR})
            endif()
            if(NOT EXISTS ${sdl_mixer_BINARY_DIR})
                file(MAKE_DIRECTORY ${sdl_mixer_BINARY_DIR})
            endif()
            add_subdirectory(${sdl_mixer_SOURCE_DIR} ${sdl_mixer_BINARY_DIR} EXCLUDE_FROM_ALL)
            list(APPEND CPP_LIBS "SDL2_mixer")
        endif()
    endif()
endif()

if(ENABLE_FREETYPE)
    if (NOT freetype_FOUND) # If there's none, fetch and build
        include(FetchContent)
        FetchContent_Declare(
                freetype
                GIT_REPOSITORY https://github.com/freetype/freetype.git
                GIT_TAG ${FREETYPE_GIT_TAG}
        )
        FetchContent_GetProperties(freetype)
        if (NOT freetype_POPULATED)
            FetchContent_Populate(freetype)
            message("freetype_LIBRARY: " ${freetype_LIBRARY}) # fail but define in cmake
            message("freetype_INCLUDE_DIR: " ${freetype_INCLUDE_DIR}) #pass
            message("freetype_SOURCE_DIR: " ${freetype_SOURCE_DIR}) # pass
            message("freetype_BINARY_DIR: " ${freetype_BINARY_DIR}) # pass

            #set(FT_WITH_ZLIB OFF CACHE BOOL "" FORCE)
            #set(FT_WITH_BZIP2 OFF CACHE BOOL "" FORCE)
            set(FT_WITH_PNG OFF CACHE BOOL "" FORCE)
            set(FT_WITH_HARFBUZZ OFF CACHE BOOL "" FORCE)
            set(FT_WITH_BROTLI OFF CACHE BOOL "" FORCE)

            # build freetype
            list(APPEND CPP_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
            list(APPEND CPP_INCLUDE_DIRS ${freetype_BINARY_DIR}/include)
            list(APPEND CPP_HEADER_FILES ${freetype_SOURCE_DIR}/include/ft2build.h)

            list(APPEND FREETYPE_INCLUDE_DIRS ${freetype_SOURCE_DIR}/include)
            list(APPEND FREETYPE_INCLUDE_DIRS ${freetype_BINARY_DIR}/include)

            set(FREETYPE_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

            if(NOT EXISTS ${freetype_SOURCE_DIR})
                file(MAKE_DIRECTORY ${freetype_SOURCE_DIR})
            endif()
            if(NOT EXISTS ${freetype_BINARY_DIR})
                file(MAKE_DIRECTORY ${freetype_BINARY_DIR})
            endif()
            add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR} EXCLUDE_FROM_ALL) #add to build in sub dir
            add_library(Freetype::Freetype ALIAS freetype)
        endif()
    endif()
endif()


#================================================
# TARGET SET UP SECTION
#================================================


#================================================
# INCLUDE DIRS
#================================================
include_directories(${CPP_INCLUDE_DIRS})
#================================================
# EXECUTE APP
#================================================
add_library(sgglib
        STATIC
        sgg/audio.cpp
        sgg/AudioManager.cpp
        sgg/fonts.cpp
        sgg/GLbackend.cpp
        sgg/graphics.cpp
        sgg/lodepng.cpp
        sgg/shader.cpp
        sgg/texture.cpp
        )

target_include_directories(sgglib PRIVATE "${sdl2_content_BINARY_DIR}/sdl2-src/include"
        "${sdl2_content_BINARY_DIR}/sdl-src/include" sgg ${INCLUDE_PATHS}
        ${SDL2_INCLUDE_DIRS})
target_link_libraries(sgglib ${CPP_LIBS} ${SDL2_LIBRARIES} freetype)
message("END OF CMAKELIST...")
