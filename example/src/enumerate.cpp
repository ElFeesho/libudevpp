#include <iostream>
#include <getopt.h>

#include <udev/udev.h>

void print_usage()
{
	std::cout << "udevpp_enumerator_example [-s subsystem-to-match] [-S subsystem-to-not-matc] [-p property-name=value-to-match] [-a sysattr{=value}]" << std::endl;
}

int main(int argc, char **argv)
{
	int arg = 0;

	std::cout << "Udevpp enumeration example" << std::endl;

	Udev::Udev udev;
	Udev::UdevEnumerate enumerator = udev.enumerate_new();

	while ((arg = getopt(argc, argv, "S:s:p:a:A:?")) != -1)
	{
		if (arg == 's')
		{
			enumerator.add_match_subsystem(std::string(optarg));
		}
		else if (arg == 'S')
		{
			enumerator.add_nomatch_subsystem(std::string(optarg));
		}
		else if (arg == 'p')
		{
			std::string property(optarg);
			if (property.find("=") == std::string::npos)
			{
				print_usage();
				return -1;
			}
			int index_eq = property.find("=");
			std::string property_name(property, 0, index_eq);
			std::string property_value(property, index_eq + 1, property.length() - (index_eq+1));
			enumerator.add_match_property(property_name, property_value);
		}
		else if(arg == 'a')
		{
			std::string systemattr(optarg);
			if (systemattr.find("=") == std::string::npos)
			{
				enumerator.add_match_sysattr(systemattr);
			}
			else
			{
				int index_eq = systemattr.find("=");
				std::string systemattr_name(systemattr, 0, index_eq);
				std::string systemattr_value(systemattr, index_eq + 1, systemattr.length() - (index_eq+1));
				enumerator.add_match_sysattr(systemattr_name, systemattr_value);
			}
		}
		else if(arg == 'A')
		{
			std::string systemattr(optarg);
			if (systemattr.find("=") == std::string::npos)
			{
				enumerator.add_nomatch_sysattr(systemattr);
			}
			else
			{
				int index_eq = systemattr.find("=");
				std::string systemattr_name(systemattr, 0, index_eq);
				std::string systemattr_value(systemattr, index_eq + 1, systemattr.length() - (index_eq+1));
				enumerator.add_nomatch_sysattr(systemattr_name, systemattr_value);
			}
		}
		else if(arg == '?')
		{
			print_usage();
			return -1;
		}
	}

	enumerator.scan_devices();

	for (Udev::UdevDevice device : enumerator.enumerate_devices())
	{
		std::cout << "System Name: " << device.get_sysname() << std::endl;
		if (device.has_devnode())
		{
			std::cout << "\tDevice node: " << device.get_devnode() << std::endl;
		}
		std::cout << "\tDevice Path: " << device.get_devpath() << std::endl;
		std::cout << "\tSystem Path: " << device.get_syspath() << std::endl;
		std::cout << "\tSubsystem: " << device.get_subsystem() << std::endl;
		for (auto sysattrs : device.get_sysattr_map())
		{
			std::cout << "\t\tAttr: " << sysattrs.first << ": " << sysattrs.second << std::endl;
		}

		for (auto property : device.get_properties())
		{
			std::cout << "\t\tProp: " << property.first << ": " << property.second << std::endl;
		}
	}

	return 0;
}
