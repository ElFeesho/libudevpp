#include <iostream>
#include <memory>
#include <udev/udev.h>

int main(int argc, char **argv)
{
	std::cout << "Udevpp Example" << std::endl;
	Udev::Udev udev;

	Udev::UdevMonitor monitor = udev.monitor_new_from_netlink();

	return 0;
}
