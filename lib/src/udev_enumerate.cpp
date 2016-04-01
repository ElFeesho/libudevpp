#include <libudev.h>
#include "udev.h"

namespace Udev
{
	UdevEnumerate::UdevEnumerate(UdevEnumerateHandle *enumerate) : handle(enumerate)
	{
	}

	UdevEnumerate::UdevEnumerate(const UdevEnumerate &other) : handle(udev_enumerate_ref(other.handle))
	{
	}

	UdevEnumerate::UdevEnumerate(UdevEnumerate &&other) : handle(other.handle)
	{
		other.handle = nullptr;
	}

	UdevEnumerate &UdevEnumerate::operator=(const UdevEnumerate &other)
	{
		udev_enumerate_ref(other.handle);
		return *this;
	}

	UdevEnumerate &UdevEnumerate::operator=(UdevEnumerate &&other)
	{
		handle = other.handle;
		other.handle = nullptr;
		return *this;
	}

	UdevEnumerate::~UdevEnumerate()
	{
		if (handle)
		{
			udev_enumerate_unref(handle);
		}
	}
}
