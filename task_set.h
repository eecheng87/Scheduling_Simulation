#ifndef TESTCASE_H
#define TESTCASE_H
#include "config.h"

/*==================[macros]=================================================*/
/* Brief Definition of the  DeclareTask Macro */
#define declare_task(name) void TASK_##name(void)

/* Brief Task Declaration of idle_task */
declare_task(idle_task);
/* Brief Task Declaration of Task T1 */
declare_task(T1);
/* Brief Task Declaration of Task T2 */
declare_task(T2);
/* Brief Task Declaration of Task T3 */
declare_task(T3);
/* Brief Task Declaration of Task T3 */
declare_task(T4);
/* Brief Task Declaration of Task T3 */
declare_task(T5);

#endif /* #ifndef TESTCASE_H */