#include "resource.h"

status_type get_resource(resource_type id)
{
    // check the resource wheather been occupied
    int i;
    task_priority_type ceil_p;
    //task_type caller_id;
    ready_queue *it = qdummy->next;

    // find res ceiling priority
    for(i = 0; i < RESOURCES_COUNT; ++i)
    {
        if(resources_id[i] == id)
        {
            ceil_p = resources_priority[i];
            i = RESOURCES_COUNT;
        }
    }
    while(it)
    {
        res_queue *rit = it->reshead;
        while(rit)
        {
            if(rit->res == id)
                return STATUS_ERROR;
            rit = rit->next;
        }
        it = it->next;
    }
    it = qdummy->next;
    while(it)
    {
        if(it->state == RUNNING)
        {
            // current `it` is trying to get res
            res_queue *retmp = (res_queue*)malloc(sizeof(res_queue));
            retmp->next = NULL;
            retmp->org_p = it->priority;
            retmp->res = id;
            it->priority = ceil_p;
            // reorder res queue
            if(it->reshead == NULL)
            {
                it->reshead = it->restail = retmp;
            }
            else
            {
                it->restail->next = retmp;
                it->restail = it->restail->next;
            }
            break; //new
        }
        it = it->next;
    }

    // new
    it->state = READY;
    swapcontext(&it->uctx,&global_main_uctx);

    status_type result = STATUS_OK;

    return result;
}

status_type release_resource(resource_type id)
{
    int valid = 0;
    ready_queue *it = qdummy->next;
    // check wheather res is occupied
    res_queue *prev;
    while(it)
    {
        if(it->restail != NULL && it->restail->res == id)
        {
            // resource is occupied
            // update `it` configure
            valid = 1;
            it->priority =  it->restail->org_p;
            re_item = it;
            // maybe need to change current state
            it->state = READY;
            break;
        }
        it = it->next;
    }
    // delete restail from queue
    prev = re_item->reshead;
    if(valid == 1 && prev!=NULL)
    {

        if(prev->next == NULL)
        {
            // only occupy one resource
            re_item->reshead = re_item->restail = NULL;
        }
        else
        {
            while(prev->next!=re_item->restail)
                prev = prev->next;
            free(re_item->restail);
            prev->next = NULL;
            re_item->restail = prev;
        }
    }


    if(valid == 0)
        return STATUS_ERROR;
    // reorder queue
    ready_queue *front = qdummy;
    ready_queue *point = qdummy;
    // (1) delete re_item from ready queue
    while(point->next!=re_item)
    {
        if(point->next!=NULL)
            point = point->next;
        else
            break;
    }
    //printf("%d\n",re_item->id);
    if(point != NULL ) //&& point->next != NULL){
    {
        point->next = re_item->next;
        re_item->next = NULL;
    }

    point = qdummy->next;
    int last = 1;
    while(1)
    {
        if(point==NULL||re_item==NULL)
            break;
        if((re_item->priority > point->priority) || (re_item->priority == point->priority && re_item->coming_time < point->coming_time ))
        {
            // insert
            front->next = re_item;
            re_item->next = point;
            last = 0;
            //re_item = NULL;
            break;
        }
        front = front->next;
        point = point->next;
    }
    if(last == 1 && re_item!=NULL)
    {
        //append to last
        front->next = re_item;
        re_item->next = NULL;
        qtail = re_item;
        //re_item = NULL;
    }



    // go back to main do reorder

    swapcontext(&re_item->uctx,&global_main_uctx);
    status_type result = STATUS_OK;

    return result;
}