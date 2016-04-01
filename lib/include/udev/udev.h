#pragma once
namespace Udev
{
	using UdevHandle = struct udev;

	class Udev
	{
	public:
		explicit Udev();
		Udev(const Udev& other);
		Udev(Udev&& other);
		Udev& operator=(const Udev& other);
		Udev& operator=(Udev&& other);
		~Udev();
	private:
		UdevHandle *handle;
	};
}
