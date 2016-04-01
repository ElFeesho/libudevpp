cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

set(SOURCES src/udev.cpp src/udev_monitor.cpp src/udev_device.cpp include/udev/udev.h)

include_directories(include/udev)

add_library(udevpp ${SOURCES})
