#ifndef TASK_H
#define TASK_H

#include "typedefine.h"
#include "config.h"

status_type activate_task(task_type id);
status_type terminate_task(void);
ucontext_t global_main_uctx;
int global_time;
ready_queue *qhead;
ready_queue *qtail;
ready_queue *qdummy;
ready_queue *re_item;
#endif /* TASK_H */