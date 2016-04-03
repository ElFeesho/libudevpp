 cmake_minimum_required(VERSION 2.8)

project ("libudevpp Unit Tests")
set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -Wl,-wrap,udev_monitor_enable_receiving")
enable_testing()
add_subdirectory (gtest-1.7.0)

include_directories (${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include ../lib/include) 

add_test(Test monitor_test)
add_executable(monitor_test monitor_test.cpp)
target_link_libraries(monitor_test gtest gtest_main udevpp udev)
