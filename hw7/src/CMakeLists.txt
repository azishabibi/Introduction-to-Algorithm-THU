cmake_minimum_required(VERSION 3.10)

project(hw7)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/)

add_executable(hw7 hw7.cpp)
find_package(OpenCV 4 QUIET)
target_link_libraries(hw7 ${OpenCV_LIBRARIES})