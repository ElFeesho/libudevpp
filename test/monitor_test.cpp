#include <libudev.h>

#include <udev/udev.h>

#include <gtest/gtest.h>

extern "C" {
	int udev_monitor_enable_receiving_return_value = 0;

	int __wrap_udev_monitor_enable_receiving(struct udev_monitor*)
	{
		return udev_monitor_enable_receiving_return_value;
	}
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
