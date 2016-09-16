#ifndef FIND_SCALE_AND_ROTATION_H
#define FIND_SCALE_AND_ROTATION_H
#include "matching_result.h"

void find_scale_and_rotation(Image *image_to_match, Image *template_image,
        CArray *fft_image, CArray *fft_template, MatchingResult *matching_result, char verbose);

/* Min / max thresholds for the scaling.
 * The algorithm generally fails for scaling factor more than 2, but allow 5
 * anyway. Anything bigger than that just won't work, so ignore it.
 * */
#define SCALE_MIN 0.2
#define SCALE_MAX 5

#endif
