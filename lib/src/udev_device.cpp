#include <libudev.h>

#include "udev.h"

namespace Udev
{
	UdevDevice::UdevDevice(UdevDeviceHandle *device) : handle(device)
	{
	}

	UdevDevice::UdevDevice(const UdevDevice &other) : handle(udev_device_ref(other.handle))
	{
	}

	UdevDevice::UdevDevice(UdevDevice &&other) : handle(other.handle)
	{
		other.handle = nullptr;
	}

	UdevDevice& UdevDevice::operator=(const UdevDevice &other)
	{
		handle = udev_device_ref(other.handle);
		return *this;
	}

	UdevDevice& UdevDevice::operator=(UdevDevice &&other)
	{
		handle = udev_device_ref(other.handle);
		other.handle = nullptr;
		return *this;
	}

	UdevDevice::~UdevDevice()
	{
		if (handle)
		{
			udev_device_unref(handle);
		}
	}

	bool UdevDevice::has_action() const
	{
		return udev_device_get_action(handle) != nullptr;
	}

	std::string UdevDevice::get_action() const
	{
		return std::string(udev_device_get_action(handle));
	}

	bool UdevDevice::has_devpath() const
	{
		return udev_device_get_devpath(handle) != nullptr;
	}

	std::string UdevDevice::get_devpath() const
	{
		return udev_device_get_devpath(handle);
	}
}
