#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H
#include<ucontext.h>

#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define STACK_SIZE 4096
/*==================[macros]=================================================*/
/* This macro shall be used to start the definition of all tasks. */
#define TASK(name) void TASK_##name(void)

/* return value of API Services */
#define STATUS_OK ((status_type)0U)
#define STATUS_ERROR ((status_type)1U)

/* state of a task */
#define SUSPENDED ((task_state_type)0U)
#define READY ((task_state_type)1U)
#define RUNNING ((task_state_type)2U)

/*********** basic type definition ***********************************/
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef unsigned short int uint16;
typedef unsigned long long uint64;

/* This type is used to represent the return value of API services */
typedef unsigned char status_type;

/*********** task configuration type definition **********************/
typedef void (*entry_point_type)(void);

typedef unsigned char task_priority_type;

typedef unsigned char task_state_type;

typedef uint32 resources_mask_type;

typedef uint8 task_total_type;

typedef uint8 task_type;

typedef task_type *task_ref_type;

/*
    Brief Task Constant type definition

    This structure defines all constants and constant pointers
    needed to manage a task.
*/
typedef struct
{
    entry_point_type entry;               /* point to the entry of this task */
    task_type id;                         /* task id */
    task_priority_type static_priority;   /* the static priority of this task */
} task_const_type;

/*********** resource configuration type definition **********************/
typedef uint8 resource_type;

/*
    self declaration
*/
typedef struct resQ
{
    struct resQ* next;
    int org_p; // last priority
    resource_type res; // -1 means doesn't occupy any res
} res_queue;

typedef struct readyQ
{
    task_type id;
    task_state_type state;
    task_priority_type priority;
    res_queue *reshead;
    res_queue *restail;
    struct readyQ* next;
    ucontext_t uctx;
    ucontext_t umain;
    int coming_time;
} ready_queue;
//ready_queue global_ready_queue;
extern ready_queue *qhead;
extern ready_queue *qtail;
extern ready_queue *qdummy;
extern ready_queue *re_item;

extern ucontext_t global_main_uctx;
extern int global_time;
#endif /* #ifndef TYPEDEFINE_H */