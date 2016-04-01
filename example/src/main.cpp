#include <stdexcept>
#include <iostream>
#include <memory>
#include <udev/udev.h>

#include <sys/select.h>
#include <signal.h>

#include "termcolor.hpp"

static bool run = true;

void interrupt_handler(int signal_raised)
{
	run = false;
	std::cout << "Caught signal" << std::endl;
}

int main(int argc, char **argv)
{
	std::cout << "Udevpp Example" << std::endl;
	signal(SIGINT, interrupt_handler);

	Udev::Udev udev;

	Udev::UdevMonitor monitor = udev.monitor_new_from_netlink();

	try
	{
		monitor.enable_receiving();
	}
	catch(std::runtime_error ex)
	{
		std::cerr << termcolor::red << "Error: " << ex.what() << termcolor::reset << std::endl;
		return -1;
	}

	fd_set monitor_set;
	timeval timeout = { .tv_sec = 1, .tv_usec = 0 };
	int monitor_fd = monitor.get_fd();
	while(run)
	{
		FD_ZERO(&monitor_set);
		FD_SET(monitor_fd, &monitor_set);
		if (select(monitor_fd + 1, &monitor_set, nullptr, nullptr, &timeout) > 0)
		{
			if (FD_ISSET(monitor_fd, &monitor_set))
			{
				try
				{
					Udev::UdevDevice device = monitor.receive_device();
					std::cout << termcolor::green << "Received Device" << termcolor::reset << std::endl;
					if (device.is_initialized())
					{
						std::cout << termcolor::green << "Device is initialized" << termcolor::reset << std::endl;
					}
					else
					{
						std::cout << termcolor::red << "Device is not initialized" << termcolor::reset << std::endl;
					}
					std::cout << "Device Path: " << device.get_devpath() << std::endl;
					std::cout << "   Sys Path: " << device.get_syspath() << std::endl;
					std::cout << "   Sys Name: " << device.get_sysname() << std::endl;

					auto sysattr_keys = device.get_sysattr_keys();
					for (auto key : sysattr_keys)
					{
						std::cout << "System Attribute key: " << key << std::endl;
					}

					if (device.has_sysattr("trigger"))
					{
						std::cout << termcolor::green << "Contains trigger system attribute" << termcolor::reset << std::endl;
					}
					else
					{
						std::cout << termcolor::red << "No trigger system attribute" << termcolor::reset << std::endl;
					}

					auto sysattrs = device.get_sysattr_map();
					if (sysattrs.size() > 0)
					{
						for (auto sysattr_pair : sysattrs)
						{
							std::cout << sysattr_pair.first << ": " << sysattr_pair.second << std::endl;
						}
					}
					else
					{
						std::cout << "No attributes" << std::endl;
					}

					if (device.has_sysnum())
					{
						std::cout << "Sys Num: " << device.get_sysnum() << std::endl;
					}

					if (device.has_driver())
					{
						std::cout << "Driver: " << device.get_driver() << std::endl;
					}

					if (device.has_action())
					{
						std::cout << "Device Action: " << device.get_action() << std::endl;
					}

					if (device.has_subsystem())
					{
						std::cout << "Device Subsystem: " << device.get_subsystem() << std::endl;
					}

					if (device.has_devtype())
					{
						std::cout << "Device Type: " << device.get_devtype() << std::endl;
					}

					if (device.has_devnode())
					{
						std::cout << "Device Node: " << device.get_devnode() << std::endl;
					}
				}
				catch(std::runtime_error ex)
				{
					std::cerr << termcolor::red << "Failed receiving device: " << ex.what() << termcolor::reset << std::endl;
				}
				std::cout << std::endl;
			}
		}
	}

	return 0;
}
