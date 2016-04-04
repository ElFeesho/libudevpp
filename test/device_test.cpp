#include <gtest/gtest.h>

#include <libudev.h>

#include <udevpp.h>

extern "C" {

	int udev_device_get_is_initialized_return_value = 0;

	extern int __real_udev_device_get_is_initialized(struct udev_device*);

	int __wrap_udev_device_get_is_initialized(struct udev_device*)
	{
		return udev_device_get_is_initialized_return_value;
	}
}

TEST(Device, canReportWhenitIsInitialized)
{
	Udev::UdevDevice device(nullptr);

	udev_device_get_is_initialized_return_value = 1;
	ASSERT_EQ(device.is_initialized(), true);
}

TEST(Device, canReportWhenitIsNotInitialized)
{
	Udev::UdevDevice device(nullptr);

	udev_device_get_is_initialized_return_value = 0;
	ASSERT_EQ(device.is_initialized(), false);
}
