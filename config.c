/*==================[inclusions]=============================================*/
#include "config.h"
#include "task_set.h"

/*==================[external data definition]===============================*/
const task_const_type task_const[TASKS_COUNT] =
{
    /* idle_task */
    {
        TASK_idle_task,      /* task entry point */
        idle_task,           /* task id */
        0,                   /* task priority */
    },
    /* TASK T1 */
    {
        TASK_T1,             /* task entry point */
        T1,                  /* task id */
        1,                   /* task priority */
    },
    /* TASK T2 */
    {
        TASK_T2,             /* task entry point */
        T2,                  /* task id */
        2,                   /* task priority */
    },
    /* TASK T3 */
    {
        TASK_T3,             /* task entry point */
        T3,                  /* task id */
        2,                   /* task priority */
    },
    /* TASK T4 */
    {
        TASK_T4,             /* task entry point */
        T4,                  /* task id */
        2,                   /* task priority */
    },
    /* TASK T5 */
    {
        TASK_T5,             /* task entry point */
        T5,                  /* task id */
        3,                   /* task priority */
    }
};

/* Brief Auto Start Tasks List */
const task_type auto_start_tasks_list[AUTO_START_TASKS_COUNT] =
{
    idle_task,
    T1,
    T2
};

/* Brief Resources ID */
const resource_type resources_id[RESOURCES_COUNT] =
{
    RESOURCE_1,      /* may be accessed by T1, T4 */
    RESOURCE_2       /* may be accessed by T4, T5 */
};

/* Brief Resources Priorities */
const task_priority_type resources_priority[RESOURCES_COUNT] =
{
    2,  /* ceiling priority of RESOURCE_1*/
    3,  /* ceiling priority of RESOURCE_2*/
};

/*==================[end of file]============================================*/