#include <libudev.h>

#include "udev.h"

namespace Udev
{
	UdevMonitor::UdevMonitor(UdevMonitorHandle *monitor) : handle(monitor)
	{
	}

	UdevMonitor::UdevMonitor(const UdevMonitor& other) : handle(udev_monitor_ref(other.handle))
	{
	}

	UdevMonitor::UdevMonitor(UdevMonitor&& other) : handle(other.handle)
	{
		other.handle = nullptr;
	}

	UdevMonitor& UdevMonitor::operator=(const UdevMonitor& other)
	{
		handle = udev_monitor_ref(other.handle);
		return *this;
	}

	UdevMonitor& UdevMonitor::operator=(UdevMonitor&& other)
	{
		handle = other.handle;
		other.handle = nullptr;
		return *this;
	}

	UdevMonitor::~UdevMonitor()
	{
		if (handle)
		{
			udev_monitor_unref(handle);
		}
	}
}
