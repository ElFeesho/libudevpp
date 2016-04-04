cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

include_directories(../lib/src)

add_executable(udevpp_example src/main.cpp)
target_link_libraries(udevpp_example udevpp udev)

add_executable(udevpp_enumerate_example src/enumerate.cpp)
target_link_libraries(udevpp_enumerate_example udevpp udev)
