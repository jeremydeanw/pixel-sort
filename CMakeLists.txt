cmake_minimum_required(VERSION 3.3)
project(PixelSort)
FIND_PACKAGE(OpenCV REQUIRED)

include_directories("${PROJECT_BINARY_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(src)
add_subdirectory(images)

set(SOURCE_FILES src/main.cpp)
add_executable(PixelSort ${SOURCE_FILES})

target_link_libraries(PixelSort ${OpenCV_LIBS})
target_link_libraries(PixelSort PixelSortSrc)

