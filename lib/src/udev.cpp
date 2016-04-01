#include <libudev.h>

#include "udev.h"

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
}
