#ifndef MATCHING_H
#define MATCHING_H

#define MAX(a,b) ((a)>(b)?(a):(b))

#include "complex_num.h"
#include "debug.h"
#include "intermediate_event.h"

unsigned int match_image(char const * image_path, const char ** template_paths,
        unsigned int n_templates, char verbose, IECallback *cb);
#endif
