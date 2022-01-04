# Testing library
FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.7)
FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2

# Tests need to be added as executables first
#add_executable(tests test.cpp)
#
## I'm using C++17 in the test
#target_compile_features(tests PRIVATE cxx_std_20)

# Should be linked to the Catch2 testing library
#target_link_libraries(tests PRIVATE Catch2::Catch2 sgg)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
#add_test(NAME mainTest COMMAND tests) # Command can be a target

add_subdirectory(step_definitions)
