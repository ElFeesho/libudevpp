#include <iostream>
#include <udev/udev.h>

int main(int argc, char **argv)
{
	std::cout << "Udevpp Example" << std::endl;
	Udev::Udev udev;
	return 0;
}
