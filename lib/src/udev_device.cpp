#include <algorithm>
#include <libudev.h>

#include "udev.h"

namespace Udev
{
	UdevDevice::UdevDevice(UdevDeviceHandle *device) : handle(device)
	{
	}

	UdevDevice::UdevDevice(const UdevDevice &other) : handle(udev_device_ref(other.handle))
	{
	}

	UdevDevice::UdevDevice(UdevDevice &&other) : handle(other.handle)
	{
		other.handle = nullptr;
	}

	UdevDevice& UdevDevice::operator=(const UdevDevice &other)
	{
		handle = udev_device_ref(other.handle);
		return *this;
	}

	UdevDevice& UdevDevice::operator=(UdevDevice &&other)
	{
		handle = udev_device_ref(other.handle);
		other.handle = nullptr;
		return *this;
	}

	UdevDevice::~UdevDevice()
	{
		if (handle)
		{
			udev_device_unref(handle);
		}
	}

	bool UdevDevice::is_initialized() const
	{
		return udev_device_get_is_initialized(handle) == 1;
	}

	bool UdevDevice::has_action() const
	{
		return udev_device_get_action(handle) != nullptr;
	}

	std::string UdevDevice::get_action() const
	{
		return std::string(udev_device_get_action(handle));
	}

	bool UdevDevice::has_devnode() const
	{
		return udev_device_get_devnode(handle) != nullptr;
	}

	std::string UdevDevice::get_devnode() const
	{
		return udev_device_get_devnode(handle);
	}

	bool UdevDevice::has_devtype() const
	{
		return udev_device_get_devtype(handle) != nullptr;
	}

	std::string UdevDevice::get_devtype() const
	{
		return udev_device_get_devtype(handle);
	}

	bool UdevDevice::has_subsystem() const
	{
		return udev_device_get_subsystem(handle) != nullptr;
	}

	std::string UdevDevice::get_subsystem() const
	{
		return udev_device_get_subsystem(handle);
	}

	std::string UdevDevice::get_devpath() const
	{
		return udev_device_get_devpath(handle);
	}

	std::string UdevDevice::get_syspath() const
	{
		return udev_device_get_syspath(handle);
	}

	std::string UdevDevice::get_sysname() const
	{
		return udev_device_get_sysname(handle);
	}

	bool UdevDevice::has_sysnum() const
	{
		return udev_device_get_sysnum(handle) != nullptr;
	}

	std::string UdevDevice::get_sysnum() const
	{
		return udev_device_get_sysnum(handle);
	}

	bool UdevDevice::has_driver() const
	{
		return udev_device_get_driver(handle) != nullptr;
	}

	std::string UdevDevice::get_driver() const
	{
		return udev_device_get_driver(handle);
	}

	bool UdevDevice::has_sysattr(const std::string named) const
	{
		auto keys = get_sysattr_keys();
		return std::find(keys.begin(), keys.end(), named) != keys.end();
	}

	std::string UdevDevice::get_sysattr(const std::string named) const
	{
		const char *value = udev_device_get_sysattr_value(handle, named.c_str());
		if (value == nullptr)
		{
			throw std::runtime_error("systemattr does not exist or could not be retrieved");
		}
		return std::string(value);
	}

	std::vector<std::string> UdevDevice::get_sysattr_keys() const
	{
		std::vector<std::string> keys;

		auto sysattr_list = udev_device_get_sysattr_list_entry(handle);
		struct udev_list_entry *entry = nullptr;
		udev_list_entry_foreach(entry, sysattr_list)
		{
			keys.emplace_back(udev_list_entry_get_name(entry));
		}

		return keys;
	}

	std::map<std::string, std::string> UdevDevice::get_sysattr_map() const
	{
		std::map<std::string, std::string> attr;
		auto sysattr_list = udev_device_get_sysattr_list_entry(handle);
		struct udev_list_entry *entry = nullptr;
		udev_list_entry_foreach(entry, sysattr_list)
		{
			const char *key = udev_list_entry_get_name(entry);
			const char *value = udev_device_get_sysattr_value(handle, key);
			if (entry != nullptr)
			{
				if (key != nullptr && value != nullptr)
				{
					attr[std::string(udev_list_entry_get_name(entry))] = std::string(value);
				}
			}
		}

		return attr;
	}

	std::vector<std::string> UdevDevice::get_devlinks() const
	{
		std::vector<std::string> links;
		struct udev_list_entry *entry = nullptr;
		udev_list_entry_foreach(entry, udev_device_get_devlinks_list_entry(handle))
		{
			links.emplace_back(udev_list_entry_get_name(entry));
		}
		return links;
	}

	bool UdevDevice::has_property(const std::string named) const
	{
		return udev_device_get_property_value(handle, named.c_str()) != nullptr;
	}

	std::string UdevDevice::get_property(const std::string named) const
	{
		return udev_device_get_property_value(handle, named.c_str());
	}

	std::map<std::string, std::string> UdevDevice::get_properties() const
	{
		std::map<std::string, std::string> property_map;
		struct udev_list_entry *entry = nullptr;
		struct udev_list_entry *properties = udev_device_get_properties_list_entry(handle);
		udev_list_entry_foreach(entry, properties)
		{
			property_map[std::string(udev_list_entry_get_name(entry))] = std::string(udev_list_entry_get_value(entry));
		}
		return property_map;
	}

	bool UdevDevice::has_tag(const std::string named) const
	{
		return udev_device_has_tag(handle, named.c_str());
	}

	std::vector<std::string> UdevDevice::get_tags() const
	{
		std::vector<std::string> tags;

		struct udev_list_entry *entry;
		struct udev_list_entry *tags_list = udev_device_get_tags_list_entry(handle);

		udev_list_entry_foreach(entry, tags_list)
		{
			tags.emplace_back(udev_list_entry_get_name(entry));
		}

		return tags;
	}
}

