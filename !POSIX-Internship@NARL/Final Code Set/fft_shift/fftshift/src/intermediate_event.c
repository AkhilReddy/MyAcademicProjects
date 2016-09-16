#include <assert.h>
#include <stdio.h>

#include "intermediate_event.h"

inline void send_event(IEventID eid, Image *img, Image *p, IECallback *cb,
        void* extra)
{
    assert(img || p);
    IntermediateEvent ev;
    ev.id = eid;
    ev.image = img;
    ev.pattern = p;
    ev.context = cb->context;
    ev.extra = extra;
    cb->func(&ev);
}
