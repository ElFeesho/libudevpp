#include <iostream>
#include <memory>
#include <udev/udev.h>

int main(int argc, char **argv)
{
	std::cout << "Udevpp Example" << std::endl;
	Udev::Udev udev;

	Udev::Udev new_udev(udev);

	Udev::Udev move_dev = std::move(udev);

	return 0;
}
