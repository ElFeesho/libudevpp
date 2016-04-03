#include <libudev.h>

#include <udev/udev.h>

#include <gtest/gtest.h>

extern "C" {
	int udev_monitor_enable_receiving_return_value = 0;
	int udev_monitor_get_fd_return_value = 0;
	const char *udev_monitor_new_from_netlink_captured_name = nullptr;

	extern struct udev_monitor* __real_udev_monitor_new_from_netlink(struct udev*, const char*);
	extern int __real_udev_device_get_is_initialized(struct udev_device *);


	int __wrap_udev_device_get_is_initialized(struct udev_device* device)
	{
		return __real_udev_device_get_is_initialized(device);
	}

	int __wrap_udev_monitor_enable_receiving(struct udev_monitor*)
	{
		return udev_monitor_enable_receiving_return_value;
	}

	int __wrap_udev_monitor_get_fd(struct udev_monitor*)
	{
		return udev_monitor_get_fd_return_value;
	}

	struct udev_monitor *__wrap_udev_monitor_new_from_netlink(struct udev* udev, const char *captured_name)
	{
		udev_monitor_new_from_netlink_captured_name = captured_name;
		return __real_udev_monitor_new_from_netlink(udev, captured_name);
	}
}

TEST(UdevMonitor, monitorWillBeCreatedForUdevByDefault) {

	udev_monitor_enable_receiving_return_value = -1;

	Udev::Udev udev;
	auto monitor = udev.monitor_new_from_netlink();
	ASSERT_EQ(udev_monitor_new_from_netlink_captured_name, "udev");
}

TEST(UdevMonitor, monitorCanBeCreatedForKernelEvents) {

	udev_monitor_enable_receiving_return_value = -1;

	Udev::Udev udev;
	auto monitor = udev.monitor_new_from_netlink("kernel");
	ASSERT_EQ(udev_monitor_new_from_netlink_captured_name, "kernel");
}

TEST(UdevMonitor, willThrowWhenItIsNotPossibleToEnableReceiving) {

	udev_monitor_enable_receiving_return_value = -1;

	Udev::Udev udev;
	auto monitor = udev.monitor_new_from_netlink();
	ASSERT_THROW(monitor.enable_receiving(), std::runtime_error);
}

TEST(UdevMonitor, willNotThrowWhenItIsPossibleToEnableReceiving) {

	udev_monitor_enable_receiving_return_value = 0;

	Udev::Udev udev;
	auto monitor = udev.monitor_new_from_netlink();
	ASSERT_NO_THROW(monitor.enable_receiving());
}

TEST(UdevMonitor, willReturnTheCorrectSocketFd) {

	udev_monitor_get_fd_return_value = 0xf;

	Udev::Udev udev;
	auto monitor = udev.monitor_new_from_netlink();
	ASSERT_EQ(monitor.get_fd(), udev_monitor_get_fd_return_value);
}
