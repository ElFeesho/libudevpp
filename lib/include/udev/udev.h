#pragma once

#include <string>

namespace Udev
{
	using UdevHandle = struct udev;
	using UdevMonitorHandle = struct udev_monitor;

	class UdevMonitor;

	class Udev
	{
	public:
		explicit Udev();
		Udev(const Udev& other);
		Udev(Udev&& other);
		Udev& operator=(const Udev& other);
		Udev& operator=(Udev&& other);
		~Udev();

		UdevMonitor monitor_new_from_netlink(const char *name = "udev");
	private:
		UdevHandle *handle;
	};


	class UdevMonitor
	{
	public:
		UdevMonitor(UdevMonitorHandle *monitor);
		UdevMonitor(const UdevMonitor &other);
		UdevMonitor(UdevMonitor &&other);
		UdevMonitor& operator=(const UdevMonitor &monitor);
		UdevMonitor& operator=(UdevMonitor &&monitor);
		~UdevMonitor();

		void enable_receiving() const;
		int get_fd() const;
	private:
		UdevMonitorHandle *handle;
	};
}
