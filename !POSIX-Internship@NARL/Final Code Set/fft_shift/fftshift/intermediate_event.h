#ifndef INTERMEDIATE_EVENT_H
#define INTERMEDIATE_EVENT_H
#include "image.h"

typedef enum {
    IE_IMAGE_LOADED,
    IE_TEMPLATE_LOADED,
    IE_LOG_POLAR_FFT,
    IE_BEST_MATCH,
    IE_LOG_POLAR1,
    IE_LOG_POLAR2,
    IE_FFT1,
    IE_FFT2,
    IE_CORR
} IEventID;

typedef struct {
    IEventID id;
    Image *image;
    Image *pattern;
    const char *description;
    void *context;
    void *extra;
} IntermediateEvent;

typedef void (*IECallbackFunction)(IntermediateEvent*);

typedef struct {
    IECallbackFunction func;
    void *context;
} IECallback;

inline void send_event(IEventID eid, Image *img, Image *p, IECallback *cb,
        void* extra);
#endif
