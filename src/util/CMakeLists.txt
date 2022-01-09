add_library(UTIL paths.cpp custom-string.cpp)

target_include_directories(UTIL PRIVATE "${CMAKE_SOURCE_DIR}/${HEADER_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE UTIL)
