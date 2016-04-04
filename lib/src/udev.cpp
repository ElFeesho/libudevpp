#include <libudev.h>
#include <assert.h>
#include <string>

#include "udevpp.h"

namespace Udev
{
	Udev::Udev() : handle(udev_new())
	{
	}

	Udev::Udev(const Udev &other) : handle(udev_ref(other.handle))
	{
	}

	Udev::Udev(Udev &&other) : handle(other.handle)
	{
		other.handle = nullptr;
	}

	Udev& Udev::operator=(const Udev &other)
	{
		this->handle = udev_ref(other.handle);
		return *this;
	}

	Udev& Udev::operator=(Udev &&other)
	{
		this->handle = other.handle;
		other.handle = nullptr;
		return *this;
	}

	Udev::~Udev()
	{
		if (handle)
		{
			udev_unref(handle);
		}
	}

	UdevMonitor Udev::monitor_new_from_netlink(const char *name)
	{
		assert(name != nullptr && (std::string(name) == "udev" || std::string(name) == "kernel"));
		return UdevMonitor(udev_monitor_new_from_netlink(handle, name));
	}

	UdevEnumerate Udev::enumerate_new()
	{
		return UdevEnumerate(udev_enumerate_new(handle));
	}
}
