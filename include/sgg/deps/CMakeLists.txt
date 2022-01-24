include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif ()

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
)

FetchContent_GetProperties(glew)
if (NOT glew_POPULATED)
    FetchContent_Populate(glew)
    add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
endif ()

FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
)

FetchContent_GetProperties(freetype)
if (NOT freetype_POPULATED)
    FetchContent_Populate(freetype)
    add_subdirectory(${freetype_SOURCE_DIR} ${freetype_BINARY_DIR})
endif ()

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
FetchContent_MakeAvailable(SDL2)
FetchContent_GetProperties(SDL2)
#if (NOT SDL2_POPULATED)
#    FetchContent_Populate(SDL2)
#    add_subdirectory(${SDL2_SOURCE_DIR} ${SDL2_BINARY_DIR})
#endif ()

FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
)
FetchContent_MakeAvailable(SDL2_mixer)
FetchContent_GetProperties(SDL2_mixer)
#if (NOT SDL2_mixer_POPULATED)
#    FetchContent_Populate(SDL2_mixer)
#    add_subdirectory(${SDL2_mixer_SOURCE_DIR} ${SDL2_mixer_BINARY_DIR})
#endif ()
