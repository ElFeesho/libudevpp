#include <stdexcept>
#include <iostream>
#include <memory>
#include <udev/udev.h>

#include <sys/select.h>
#include <signal.h>

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
		std::cerr << "Error: " << ex.what() <<  std::endl;
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
				std::cout << "Received event" << std::endl;
				try
				{
					Udev::UdevDevice device = monitor.receive_device();
					if (device.has_action())
					{
						std::cout << "Device Action: " << device.get_action() << std::endl;
					}
				}
				catch(std::runtime_error ex)
				{
					std::cerr << "Failed receiving device: " << ex.what() << std::endl;
				}
			}
		}
	}

	return 0;
}
