cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

set(SOURCES src/main.cpp)

include_directories(../lib/include)

add_executable(udevpp_example ${SOURCES})
target_link_libraries(udevpp_example udevpp)
