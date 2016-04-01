#include <stdexcept>
#include <iostream>
#include <memory>
#include <udev/udev.h>

int main(int argc, char **argv)
{
	std::cout << "Udevpp Example" << std::endl;
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

	return 0;
}
