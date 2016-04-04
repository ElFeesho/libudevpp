project(Udevpp)

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

set(SOURCES src/udev.cpp src/udev_enumerate.cpp src/udev_monitor.cpp src/udev_device.cpp src/udevpp.h)

add_library(udevpp ${SOURCES})
