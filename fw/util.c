#include "util.h"

void *memset(void *dst, int value, size_t n)
{
    unsigned char *p = dst;
    while (n--)
    {
        *p++ = (unsigned char)value;
    }
    return dst;
}

