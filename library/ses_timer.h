#ifndef SES_TIMER_H_
#define SES_TIMER_H_



/*PROTOTYPES *****************************************************************/


/**type of function pointer used as timer callback
 */
typedef void (*pTimerCallback)(void);


/**
 * Sets a function to be called when the timer fires. If NULL is
 * passed, no callback is executed when the timer fires.
 *
 * @param cb  valid pointer to callback function
 */
void timer0_setCallback(pTimerCallback cb);

/**
 * Starts hardware timer 0 of MCU with a period
 * of 1 ms.
 */
void timer0_start();


/**
 * Stops timer 0.
 */
void timer0_stop();
void timer3_start();


/**
 * Stops timer 0.
 */
void timer3_stop();

/**
 * Sets a function to be called when the timer fires.
 *
 * @param cb  pointer to the callback function; if NULL, no callback
 *            will be executed.
 */
void timer1_setCallback(pTimerCallback cb);


/**
 * Start timer 1 of MCU to trigger on compare match every 5ms.
 */
void timer1_start();


/**
 * Stops timer 1 of the MCU if it is no longer needed.
 */
void timer1_stop();

#endif /* SES_TIMER_H_ */
