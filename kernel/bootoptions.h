#ifndef _BOOTOPSTIONS_H
#define _BOOTOPSTIONS_H

#include "ports.h"

#define reboot() outb(0x64, 0xfe);

#endif