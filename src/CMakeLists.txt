add_executable(${PROJECT_NAME} main.cpp App.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
#target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")

set(SUBMODULES sounds hud graphics game util)
foreach(MODULE ${SUBMODULES})
    add_subdirectory(${MODULE})
endforeach()

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        sgg
        ${SGG_LIBS}
)
