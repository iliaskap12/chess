add_executable(${PROJECT_NAME} main.cpp App.cpp)
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)
#target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address -O1 -fno-omit-frame-pointer)
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        "${SRC_DIR}"
        "${SRC_DIR}/graphics"
        "${SRC_DIR}/game"
        "${SRC_DIR}/util"
        "${SRC_DIR}/sounds"
        "${SRC_DIR}/hud"
)

set(SUBMODULES sounds hud graphics game util)
foreach (MODULE ${SUBMODULES})
    add_subdirectory(${MODULE})
endforeach ()

find_package(sgg REQUIRED)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        sgg::sgg
)
