#include <stddef.h>
#include <stdint.h>
#if defined(_WIN32) // If compiling for windows
#include <windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")
