/*
 * Simple command line program to test the digit matching.
 */
#include <stdio.h>
#include <string.h>

#include "matching.h"
#include "patterns.h"

int main(int argc, const char *argv[])
{
    unsigned int i;
    char verbose = 0;

    for (i = 1; i < argc; ++i)
    {
        if (strncmp(argv[i], "-v", 3) == 0)
        {
            verbose = VERBOSE_DEBUG;
            continue;
        }
        match_image(argv[i], PATTERNS, NUM_PATTERNS, verbose, NULL);
    }
    return 0;
}
