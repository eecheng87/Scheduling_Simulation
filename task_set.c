#include "task_set.h"
#include "task.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>

TASK(T1)
{
    printf("In T1\n");

    printf("T1 try to get RESOURCE_1\n");
    if(get_resource(RESOURCE_1) == STATUS_OK)
        printf("T1 got RESOURCE_1\n");

    printf("T1 try to activate T3\n");
    if(activate_task(T3) == STATUS_OK)
        printf("T1 return from activate_task(T3)\n");

    printf("T1 try to activate T5\n");
    if(activate_task(T5) == STATUS_OK)
        printf("T1 return from activate_task(T5)\n");

    printf("T1 try to release RESOURCE_1\n");
    if(release_resource(RESOURCE_1)== STATUS_OK)
        printf("T1 return from release_resource(RESOURCE_1)\n");

    printf("T1 terminated\n");
    terminate_task();
}

TASK(T2)
{
    printf("In T2\n");

    printf("T2 try to activate T2\n");
    if(activate_task(T2) == STATUS_ERROR)
        printf("T2 failed to activate T2\n");
    else
        printf("==Please implement error checking mechanism!==\n");

    printf("T2 try to activate T4\n");
    if(activate_task(T4) == STATUS_OK)
        printf("T2 return from activate_task(T4)\n");

    printf("T2 try to activate T3\n");
    if(activate_task(T3) == STATUS_OK)
        printf("T2 return from activate_task(T3)\n");

    printf("T2 terminated\n");
    terminate_task();
}

TASK(T3)
{
    printf("In T3\n");

    printf("T3 try to activate T1\n");
    if(activate_task(T1) == STATUS_ERROR)
        printf("T3 failed to activate T1\n");
    else
        printf("==Please implement error checking mechanism!==\n");

    printf("T3 terminated\n");
    terminate_task();
}

TASK(T4)
{
    printf("In T4\n");

    printf("T4 try to get RESOURCE_1\n");
    if(get_resource(RESOURCE_1) == STATUS_OK)
        printf("T4 got RESOURCE_1\n");

    printf("T4 try to get RESOURCE_2\n");
    if(get_resource(RESOURCE_2) == STATUS_OK)
        printf("T4 got RESOURCE_2\n");

    printf("T4 try to activate T5\n");
    if(activate_task(T5) == STATUS_OK)
        printf("T4 return from activate_task(T5)\n");

    printf("T4 try to release RESOURCE_2\n");
    if(release_resource(RESOURCE_2)== STATUS_OK)
        printf("T4 return from release_resource(RESOURCE_2)\n");

    printf("T4 try to release RESOURCE_1\n");
    if(release_resource(RESOURCE_1)== STATUS_OK)
        printf("T4 return from release_resource(RESOURCE_1)\n");

    printf("T4 terminated\n");
    terminate_task();
}

TASK(T5)
{
    printf("In T5\n");

    printf("T5 try to get RESOURCE_2\n");
    if(get_resource(RESOURCE_2) == STATUS_OK)
        printf("T5 got RESOURCE_2\n");

    printf("T5 try to get RESOURCE_2\n");
    if(get_resource(RESOURCE_2) == STATUS_ERROR)
        printf("T5 failed to get RESOURCE_2\n");
    else
        printf("==Please implement error checking mechanism!==\n");

    printf("T5 try to terminate\n");
    if(terminate_task() == STATUS_ERROR)
        printf("T5 failed to terminate\n");
    else
        printf("==Please implement error checking mechanism!==\n");

    printf("T5 try to release RESOURCE_2\n");
    if(release_resource(RESOURCE_2)== STATUS_OK)
        printf("T5 return from release_resource(RESOURCE_2)\n");

    printf("T5 try to release RESOURCE_2\n");
    if(release_resource(RESOURCE_2)== STATUS_ERROR)
        printf("T5 failed to release RESOURCE_2\n");
    else
        printf("==Please implement error checking mechanism!==\n");

    printf("T5 terminated\n");
    terminate_task();
}

TASK(idle_task)
{
    printf("In idle_task\n");
    exit(0);
}