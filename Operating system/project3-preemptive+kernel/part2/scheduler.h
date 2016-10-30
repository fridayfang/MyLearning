#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "common.h"
#include "queue.h"

typedef enum {
    KERNEL_THREAD,
    PROCESS
} task_type_t;

typedef int priority_t;

typedef enum {
    FIRST_TIME,
    READY,
    BLOCKED,
    EXITED,
    SLEEPING
} status_t;

/* Simplified structure, used
 * in tasks.c to declare all
 * processes to start.
 */
struct task_info {
    uint32_t entry_point;
    task_type_t task_type;
};

/* Two macros for initializing a task_info structure */
#define TH(entry)   { .entry_point = (uint32_t) entry,	\
      .task_type = KERNEL_THREAD }
#define PROC(entry) { .entry_point = (uint32_t) entry,	\
      .task_type = PROCESS }

/* Process control block */
typedef struct pcb {
  /* Do not change the order of this! entry.S depends on the precise ordering of fields following this
     comment */
  node_t node;
  uint32_t kflags;
  uint32_t kregs[8];
  uint32_t *ksp;
  uint32_t uflags;
  uint32_t uregs[8];
  uint32_t *usp;
  int nested_count;
  /* Ok, you may change the order from now on*/
  uint32_t entry_point;
  pid_t pid;
  task_type_t task_type;
  status_t status;
  uint32_t entry_count; // how many times this task has been pre-emtped to
  uint64_t deadline;
  /* Extra credit */
  priority_t priority;
  void* blocking_lock;
} pcb_t;

extern node_t ready_queue;
extern node_t sleep_wait_queue;
extern pcb_t *current_running;

/* Save the context and the kernel stack before calling scheduler.  This
   function is implemented in entry.S */
extern void scheduler_entry(void);

/* Schedule another task.  Call from a kernel thread or
   kernel_entry_helper() */
void do_yield(void);

/* Schedule another task.  Do not reschedule the current one.  Call from a
   kernel thread or kernel_entry_helper() */
void do_exit(void);

/* Return the current task's pid */
pid_t do_getpid(void);

/* Milliseconds since boot */
uint64_t do_gettimeofday(void);

/* Sleep for specified number of mulliseconds */
void do_sleep(int milliseconds);

/* Schedule another task, putting the current one in the specified queue.
   Do not reschedule the current task until it is unblocked */
void block(node_t * wait_queue);

/* Unblock the specified task */
void unblock(pcb_t * task);

/* Extra Credit */
/* Return the current task's priority */
priority_t do_getpriority(void);

/* Extra Credit */
/* Set the current task's priority */
void do_setpriority(priority_t priority);

#endif                          /* SCHEDULER_H */
