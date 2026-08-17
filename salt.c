#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32)
#include <windows.h>
#include <bcrypt.h>

int get_random_bytes(void *buf, size_t len) {
    return BCryptGenRandom(NULL, (PUCHAR)buf, (ULONG)len,
                           BCRYPT_USE_SYSTEM_PREFERRED_RNG) == 0;
}

#elif defined(__linux__)
#include <fcntl.h>
#include <unistd.h>
