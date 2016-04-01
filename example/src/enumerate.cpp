#include <iostream>

#include <udev/udev.h>

int main(int argc, char **argv)
{
	std::cout << "Udevpp enumeration example" << std::endl;

	Udev::Udev udev;
	Udev::UdevEnumerate enumerator = udev.enumerate_new();

	enumerator.add_match_subsystem("input");

	for (Udev::UdevDevice device : enumerator.enumerate_devices())
	{
		std::cout << "Device Path: " << device.get_devpath() << std::endl;
		std::cout << "System Path: " << device.get_syspath() << std::endl;
	}

	return 0;
}
