cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -Wl,-wrap,udev_monitor_enable_receiving,-wrap,udev_monitor_get_fd,-wrap,udev_monitor_new_from_netlink,-wrap,udev_device_get_is_initialized")
enable_testing()
add_subdirectory (gtest-1.7.0)

include_directories (${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include ../lib/src) 

add_executable(monitor_test monitor_test.cpp)
add_executable(device_test device_test.cpp)
target_link_libraries(monitor_test gtest gtest_main udevpp udev)
target_link_libraries(device_test gtest gtest_main udevpp udev)

add_test(MonitorTest monitor_test)
add_test(DeviceTest device_test)
