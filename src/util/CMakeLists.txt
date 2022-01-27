add_library(UTIL src/paths.cpp src/custom-string.cpp)

target_include_directories(
        UTIL
        PRIVATE
        "${SRC_DIR}/util"
        "${SRC_DIR}/util/util"
)
target_link_libraries(${PROJECT_NAME} PRIVATE UTIL)
