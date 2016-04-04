#include <libudev.h>
#include "udevpp.h"

#include <iostream>

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

	void UdevEnumerate::add_match_subsystem(const std::string subsystem) const
	{
		udev_enumerate_add_match_subsystem(handle, subsystem.c_str());
	}

	void UdevEnumerate::add_nomatch_subsystem(const std::string subsystem) const
	{
		udev_enumerate_add_nomatch_subsystem(handle, subsystem.c_str());
	}

	void UdevEnumerate::add_match_sysattr(const std::string sysattr, const std::string value) const
	{
		udev_enumerate_add_match_sysattr(handle, sysattr.c_str(), value.length() > 0 ? value.c_str() : nullptr);
	}

	void UdevEnumerate::add_nomatch_sysattr(const std::string sysattr, const std::string value) const
	{
		udev_enumerate_add_nomatch_sysattr(handle, sysattr.c_str(), value.length() > 0 ? value.c_str() : nullptr);
	}

	void UdevEnumerate::add_match_property(const std::string property, const std::string value) const
	{
		udev_enumerate_add_match_property(handle, property.c_str(), value.c_str());
	}

	void UdevEnumerate::add_match_tag(const std::string tag) const
	{
		udev_enumerate_add_match_tag(handle, tag.c_str());
	}

	void UdevEnumerate::add_match_is_initialized() const
	{
		udev_enumerate_add_match_is_initialized(handle);
	}

	void UdevEnumerate::scan_devices() const
	{
		udev_enumerate_scan_devices(handle);
	}

	void UdevEnumerate::scan_subsystems() const
	{
		udev_enumerate_scan_subsystems(handle);
	}

	std::vector<UdevDevice> UdevEnumerate::enumerate_devices() const
	{
		std::vector<UdevDevice> devices;
		struct udev_list_entry *entry = nullptr;
		struct udev_list_entry *enumeration_list = udev_enumerate_get_list_entry(handle);
		udev_list_entry_foreach(entry, enumeration_list)
		{
			const char *device_path = udev_list_entry_get_name(entry);
			devices.emplace_back(udev_device_new_from_syspath(udev_enumerate_get_udev(handle), device_path));
		}

		return devices;
	}
}
