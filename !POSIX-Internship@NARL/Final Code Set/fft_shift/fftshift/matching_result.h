#ifndef MATCHING_RESULT
#define MATCHING_RESULT
#include "image.h"

typedef struct
{
    double max_correlation;
    unsigned int template_index;
    double scale;
    double rotation;
    unsigned int shift_x;
    unsigned int shift_y;
    Image *image_fft;
    Image *image_logpolar;
    Image *log_polar_fft_correlation;
    Image *template_fft;
    Image *template_image;
    Image *template_logpolar;
} MatchingResult;

MatchingResult* matching_result_alloc();
#endif
