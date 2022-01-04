# Tests need to be added as executables first
add_executable(start_game_feature start_game.cpp "${CMAKE_SOURCE_DIR}/src/App.cpp")

target_include_directories(start_game_feature PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}" "${CMAKE_SOURCE_DIR}")

# I'm using C++17 in the test
target_compile_features(start_game_feature PRIVATE cxx_std_20)

# Should be linked to the Catch2 testing library
target_link_libraries(
        start_game_feature
        PRIVATE
        Catch2::Catch2
        sgg
        ${GAME_LIBS}
        ${SGG_LIBS}
)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME start_game_feature COMMAND start_game_feature) # Command can be a target
