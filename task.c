#include "task.h"

status_type activate_task(task_type id)
{
    int valid = 1;
    ready_queue *tmp = qdummy->next;
    ready_queue *caller;
    // find caller
    while(tmp)
    {
        if(tmp->state == RUNNING)
        {
            //tmp->state = READY;
            caller = tmp;
            break;
        }
        tmp = tmp->next;
    }
    tmp = qdummy->next;
    while(tmp)
    {
        if(tmp->id == id)
        {
            valid = 0;
            break;
        }
        tmp = tmp->next;
    }
    if(valid == 0)
    {
        return STATUS_ERROR;
    }
    // activate should be valid
    // fill new node
    ready_queue *node = (ready_queue*)malloc(sizeof(ready_queue));
    node->state = READY;
    node->id = id;
    node->coming_time = ++global_time;
    getcontext(&node->uctx);
    node->uctx.uc_stack.ss_sp = malloc(STACK_SIZE);
    node->uctx.uc_stack.ss_size = STACK_SIZE;
    node->uctx.uc_stack.ss_flags = 0;
    node->uctx.uc_link = &global_main_uctx;
    makecontext(&node->uctx,task_const[id].entry,0);
    node->next = NULL;
    node->priority = task_const[id].static_priority;
    node->reshead = node->restail = NULL;
    status_type result = STATUS_OK;

    // reorder queue
    ready_queue *prev = qdummy;
    ready_queue *pointer = qdummy->next;
    if(pointer == NULL)
        qdummy->next = qtail = node;
    while(pointer)
    {
        if((node->priority > pointer->priority) || (node->priority == pointer->priority && node->coming_time < pointer->coming_time ))
        {
            // insert
            prev->next = node;
            node->next = pointer;
            break;
        }
        prev = prev->next;
        pointer = pointer->next;
    }

    // jump
    if(node->priority > caller->priority)
    {
        caller->state = READY; // rechoose by main
        swapcontext(&caller->uctx,&global_main_uctx);
    }


    return result;
}

status_type terminate_task(void)
{
    // check who is running
    //task_type run_id;
    ready_queue *tmp = qdummy->next;
    ready_queue *prev = qdummy;
    while(tmp)
    {
        if(tmp->state == RUNNING)
        {

            // run_id = tmp->id;
            tmp->state = SUSPENDED;
            break;
        }
        prev = prev->next;
        tmp = tmp->next;
    }
    // if still occupy resource
    if(tmp!=NULL&&tmp->reshead!=NULL)
        return STATUS_ERROR;
    // delete node from ready queue
    if(tmp!=NULL)
    {
        prev->next = tmp->next;
        free(tmp);
    }
    // if tmp is tail, update qtail
    if(prev->next == NULL)
        qtail = prev;
    status_type result = STATUS_OK;

    return result;
}