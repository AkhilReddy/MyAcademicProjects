#include "stdlib.h"

#include "matching_result.h"
#include "xmalloc.h"

MatchingResult* matching_result_alloc()
{
    MatchingResult *matching_result = xmalloc(sizeof(MatchingResult));
    matching_result->template_index = -1;
    matching_result->max_correlation = 0.0;
    return matching_result;
}
