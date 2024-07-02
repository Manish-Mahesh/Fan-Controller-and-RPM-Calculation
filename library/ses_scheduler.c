/* INCLUDES *******************************************************************/
#include <stdlib.h>
#include <util/atomic.h>
#include "ses_timer.h"
#include "ses_scheduler.h"

/* PRIVATE VARIABLES *********************************************************/
static task_descriptor_t *taskList = NULL;

/* FUNCTION DEFINITIONS *****************************************************/

// This function will be called every 1 ms
static void scheduler_update(void) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        task_descriptor_t *curr = taskList;
        while (curr != NULL) {
            if (curr->expire > 0) {
                curr->expire--;
            }
            if (curr->expire == 0 && curr->execute == 0) {
                curr->execute = 1;
                if (curr->period > 0) {
                    curr->expire = curr->period;
                }
            }
            curr = curr->next;
        }
   }
}

void scheduler_init() {
    taskList = NULL;
    timer0_setCallback(scheduler_update);
    timer0_start();
}

void scheduler_run() {
    while (1) {
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            task_descriptor_t *curr = taskList;
            task_descriptor_t *prev = NULL;

            while (curr != NULL) {
                if (curr->execute) {
                    curr->execute = 0;  // Reset the execute flag
                    curr->task(curr->param);  // Execute the task

                    if (curr->period == 0) {
                        // Remove one-shot tasks
                        if (prev == NULL) {
                            // Head of the list
                            taskList = curr->next;
                            curr = taskList;
                        } else {
                            prev->next = curr->next;
                            curr = curr->next;
                        }
                        continue;
                    }
                }
                prev = curr;
                curr = curr->next;
            }
       }
    }
}

bool scheduler_add(task_descriptor_t *toAdd) {
    if (toAdd == NULL) {
        return false;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        task_descriptor_t *curr = taskList;
        while (curr != NULL) {
            if (curr == toAdd) {
                return false;  // Task is already in the list
            }
            curr = curr->next;
        }
        // Initialize the new task
        toAdd->next = taskList;
        toAdd->expire = toAdd->period;
        toAdd->execute = 0;
        taskList = toAdd;
    }
    return true;
}

void scheduler_remove(const task_descriptor_t *toRemove) {
    if (toRemove == NULL || taskList == NULL) {
        return;
    }
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        if (taskList == toRemove) {
            taskList = taskList->next;
            return;
        }
        task_descriptor_t *curr = taskList;
        while (curr != NULL && curr->next != toRemove) {
            curr = curr->next;
        }
        if (curr != NULL && curr->next == toRemove) {
            curr->next = toRemove->next;
        }
    }
}

