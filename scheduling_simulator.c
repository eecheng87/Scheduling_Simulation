#include "typedefine.h"
#include "resource.h"
#include "task.h"


ucontext_t uctx[TASKS_COUNT];
ucontext_t uctx_main;
ucontext_t global_main_uctx;
int global_time;
ready_queue *qhead;
ready_queue *qtail;
ready_queue *qdummy;
ready_queue *re_item;
void init_task();
void reorder_queue();
int main()
{
    init_task();
    while (1)
    {
        getcontext(&global_main_uctx);
        // go back point: from release res
        ready_queue *rpoint = qdummy->next;
        ready_queue *rprev = NULL;

        // update state ( only one is RUNNING )
        // rprev is temp var to memorize who is the only one RUNNING
        while(rpoint)
        {
            if(rpoint->state == RUNNING||rpoint->state == READY)
            {
                if(rprev == NULL)
                {
                    // doesn't need to compare
                    rprev = rpoint;
                }
                else if((rprev->priority<rpoint->priority)||(rprev->priority==rpoint->priority&&rprev->coming_time>rpoint->coming_time))
                {
                    rprev->state = READY;
                    rprev = rpoint;
                }
            }
            rpoint = rpoint->next;
        }
        rprev->state = RUNNING;
        // enter new job
        rprev = qdummy;
        rpoint = qdummy->next;
        while(rpoint)
        {
            if(rpoint->state == RUNNING)
            {
                rpoint->state = RUNNING;
                setcontext(&rpoint->uctx);
            }
        }
    };
    return 0;
}
void init_task()
{
    // push auto start task into ready queue
    int i;

    qdummy = (ready_queue*)malloc(sizeof(ready_queue));
    qdummy->next = NULL;
    for(i = 0; i < AUTO_START_TASKS_COUNT; i++)
    {
        ready_queue *qtmp = (ready_queue*)malloc(sizeof(ready_queue));
        qtmp->id = task_const[auto_start_tasks_list[i]].id;
        getcontext(&qtmp->uctx);
        qtmp->uctx.uc_stack.ss_sp = malloc(STACK_SIZE);
        qtmp->uctx.uc_stack.ss_size = STACK_SIZE;
        qtmp->uctx.uc_stack.ss_flags = 0;
        qtmp->uctx.uc_link = &global_main_uctx;
        makecontext(&qtmp->uctx,task_const[auto_start_tasks_list[i]].entry,0);
        qtmp->next = NULL;
        qtmp->state = READY;
        qtmp->priority = task_const[auto_start_tasks_list[i]].static_priority;
        //qtmp->res = -1;
        qtmp->reshead = qtmp->restail = NULL;
        qtmp->coming_time = ++global_time;
        if(qdummy->next == NULL)  // queue is empty
        {
            qdummy->next = qtail = qtmp;
        }
        else
        {
            int insert = 0;
            ready_queue *slow = qdummy;
            ready_queue *fast = qdummy->next;
            while(fast)
            {
                if((qtmp->priority > fast->priority) || (qtmp->priority == fast->priority && qtmp->coming_time < fast->coming_time ))
                {
                    // insert
                    slow->next = qtmp;
                    qtmp->next = fast;
                    insert = 1;
                    break;
                }
                slow = slow->next;
                fast = fast->next;
            }
            if(insert == 0)
            {
                // un insert
                qtail->next = qtmp;
                qtail = qtail->next;
            }
        }
    }

}


