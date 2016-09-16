#include <stdlib.h>

#include "die.h"

void *xmalloc(size_t size)
{
    if (!size)
        die("Tried to allocate zero bytes");

    void *ret = malloc(size);

    if (!ret)
        die("Could not allocate memory");

    return ret;
}
