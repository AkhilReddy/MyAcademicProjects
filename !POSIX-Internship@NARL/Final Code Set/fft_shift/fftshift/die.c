#include "stdio.h"

#include "die.h"

void die(const char* err)
{
    fprintf(stderr, "ERROR: %s\n", err);
}
