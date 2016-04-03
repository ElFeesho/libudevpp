# libudevpp ![Build Status](https://travis-ci.org/ElFeesho/libudevpp.svg)
libudevpp is a small wrapper around libudev to provide an OOD approach to using libudev functionality

## Implementation Progress
The [libudev documentation](http://mirror.linux.org.au/linux/utils/kernel/hotplug/libudev/ch01.html) is being used as a guide to cover functionality in libuev. 

There is only currently partial coverage of libudev:

 * `udev` - no log methods implemented
 * `udev_device` - several methods missing
 * `udev_monitor` - several methods missing, such as filtering
 * `udev_enumerate` - All implemented apart from `udev_enumerate_add_match_parent`
 * `udev_queue` - No implementation
 
