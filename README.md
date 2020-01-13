# Scheduling_Simulation
Implement scheduling through ucontext


## Overview 
![](https://i.imgur.com/Ncg0UaM.png)


## Task State
- suspended: The task is not
active and can be activated.
- ready: The task is preempted
or activated. The task should
be put into the ready queue,
waiting for allocation of the
processor.
- running: The processor is
assigned to the task, so that
its instructions can be
executed

## Scheduling Policy
- Preemptive scheduling: The task in running state would be
preempted and be transferred into ready state, as soon as a
higher-priority task has got ready.
- The context of the preempted task should be saved so that the
task could be continued from where it was preempted.
- Tasks with equal priority are started depending on their order
of activation.
## Ready Queue
- Maintain a ready queue only for tasks in ready state.
- There is no requirement of data structure for the ready queue.

## API Description
- `status_type activate_task(task_type id)`
    - The task with <id> is transferred from suspended state
into ready state.
    - Tasks transferred from suspended state into ready state
should start from entry point of the task.
    - If the task with <id> is not in suspended state, the
activation is ignored.
    - Reschedule if needed.
    - Return STATUS_OK if no error.
    - Return STATUS_ERROR if the task with <id> is not in
suspended state.

- `status_type terminate_task(void)`
    - The calling task is transferred from running state into
suspended state.
    - If the calling task still occupies any resource, the
termination is ignored.
    - Reschedule if needed.
    - Return STATUS_OK if no error.
    - Return STATUS_ERROR if the calling task still occupies
any resource

- `status_type get_resource(resource_type id)`
    - The calling task occupies the resource with <id>.
    - If a task got a resource and its current priority is lower
than the ceiling priority of the resource, the priority of
the task would raise to the ceiling priority of the
resource.
    - If the resource with <id> is already occupied, the above
operations are ignored.
    - Return STATUS_OK if no error.
    - Return STATUS_ERROR if the resource with <id> is
already occupied.

- `status_type release_resource(resource_type id)`
    - The calling task releases the resource with <id>.
    - If a task released a resource, the priority of the task
would be reset to the priority before getting that resource.
    - If the calling task attempts to release a resource that is
not occupied by the calling task, the above operations are
ignored.
    - Reschedule if needed.
    - Return STATUS_OK if no error.
    - Return STATUS_ERROR if the calling task attempt to
release a resource that is not occupied by the calling task

## How to build
- `make testcase1` to set up testcase1 

## Correctness

- pass all testbench from `OSLab`

