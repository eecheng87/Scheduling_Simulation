#ifndef CONFIG_H
#define CONFIG_H

/*==================[inclusions]=============================================*/
#include "typedefine.h"

/*==================[macros]=================================================*/
/* Brief Task Definition */
/* The task id starts from 1 */
#define idle_task 0
#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5

/* Brief Count of all tasks */
/* The count includes real tasks and 1 idle task */
#define TASKS_COUNT 6U

/* Brief Count of priority */
#define PRIORITY_COUNT 4U

#define AUTO_START_TASKS_COUNT 3U

/* Brief Definition of the resource resource1 */
#define RESOURCE_1 ((resource_type)0)
/* Brief Definition of the resource resource2 */
#define RESOURCE_2 ((resource_type)1)

/* Brief Count of resources */
#define RESOURCES_COUNT 2


/*==================[external data declaration]==============================*/
/* Brief Tasks Constants */
extern const task_const_type task_const[TASKS_COUNT];

/* Brief Autostart Tasks List */
extern const task_type auto_start_tasks_list[AUTO_START_TASKS_COUNT];

/* Brief Resources id */
extern const resource_type resources_id[RESOURCES_COUNT];

/* Brief Resources Priorities */
extern const task_priority_type resources_priority[RESOURCES_COUNT];

/*==================[end of file]============================================*/

#endif /* #ifndef CONFIG_H */