#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/* INCLUDES *****************************************************************/
#include <stdbool.h>
#include <stdint.h>

/* TYPES ********************************************************************/

/**
 * Type of function pointer for tasks
 */
typedef void (* task_t)(void *);

/**
 * Task structure to schedule tasks
 */
typedef struct task_descriptor_s {
   task_t task;          ///< function pointer to call
   void *  param;        ///< pointer, which is passed to task when executed
   uint16_t expire;      ///< time offset in ms, after which to call the task
   uint16_t period;      ///< period of the timer after firing; 0 means exec once
   uint8_t execute:1;    ///< for internal use
   uint8_t reserved:7;   ///< reserved
   struct task_descriptor_s * next; ///< pointer to next task, internal use
} task_descriptor_t;


/* FUNCTION PROTOTYPES *******************************************************/

/**
 * Initializes the task scheduler. Uses hardware timer0 of the AVR.
 */
void scheduler_init(void);

/**
 * Runs scheduler in an infinite loop.
 */
void scheduler_run(void);

/**
 * Adds a new task to the scheduler.
 *
 * @param td   Pointer to taskDescriptor structure. The scheduler takes
 *             possesion of the memory pointed at by td until the task
 *             is removed by scheduler_remove or a non-periodic task is
 *             executed. td->expire and td->execute are written to by
 *             the task scheduler
 *
 * @return     false, if task is already present or invalid (NULL)
 *             true, if task was successfully added to scheduler and will be
 *             scheduled after td->expire ms
 */
bool scheduler_add(task_descriptor_t * td);

/**
 * Removes a timer task from the scheduler.
 *
 * @param td   pointer to task descriptor to remove
 * */
void scheduler_remove(const task_descriptor_t * td);

#endif /* SCHEDULER_H_ */
