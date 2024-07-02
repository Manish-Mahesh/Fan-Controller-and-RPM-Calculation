#ifndef SES_FAN_H_
#define SES_FAN_H_

#include <stdint.h>

/**
 * Initializes the fan module.
 *
 * This function sets up the necessary hardware configurations for the fan,
 * including setting the appropriate pins as output and configuring any
 * required timers or PWM modules. 
 */
void fan_init(void);


/**
 * Enables the fan.
 *
 * This function turns on the fan by activating the appropriate hardware
 * controls. After calling this function, the fan will start
 * running at the duty cycle previously set by `fan_setDutyCycle` or at a
 * default duty cycle if none was set.
 */
void fan_enable(void);


/**
 * Disables the fan.
 *
 * This function turns off the fan by deactivating the appropriate hardware
 * controls. The fan will stop running until `fan_enable` is called again.
 * This does not change the duty cycle setting, which will be applied when
 * the fan is enabled again.
 */
void fan_disable(void);



/**
 * Sets the duty cycle of the fan.
 *
 * @param dc   Duty cycle value to set for the fan. This should be a value
 *             between 0 and 255, where 0 represents 0% duty cycle (fan off)
 *             and 255 represents 100% duty cycle (fan running at full speed).
 *
 * This function adjusts the speed of the fan by setting the PWM duty cycle.
 *
 */
void fan_setDutyCycle(uint8_t dc);



#endif /* SES_FAN_H_ */
