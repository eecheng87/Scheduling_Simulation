#ifndef RESOURCE_H
#define RESOURCE_H

#include "typedefine.h"
#include "config.h"

status_type get_resource(resource_type id);
status_type release_resource(resource_type id);
ucontext_t global_main_uctx;
int global_time;
ready_queue *qhead;
ready_queue *qtail;
ready_queue *qdummy;
ready_queue *re_item;
#endif /* RESOURCE_H */