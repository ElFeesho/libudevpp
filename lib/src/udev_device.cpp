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
}
