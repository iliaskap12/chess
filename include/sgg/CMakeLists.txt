add_library(sgg
        sgg/audio.cpp
        sgg/AudioManager.cpp
        sgg/fonts.cpp
        sgg/GLbackend.cpp
        sgg/graphics.cpp
        sgg/lodepng.cpp
        sgg/shader.cpp
        sgg/texture.cpp
        )

add_subdirectory(deps)

target_link_libraries(sgg freetype SDL2 SDL2_mixer glm GLEW)
