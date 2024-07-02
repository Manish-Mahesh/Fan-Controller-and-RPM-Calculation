#ifndef SES_FANSPEED_H
#define SES_FANSPEED_H

#include <avr/io.h>
/**
 * Timer1 callback function.
 *
 * This function is called by the Timer1 interrupt handler at regular intervals
 * to calculate the fan speed in RPM. It reads the edge count accumulated over
 * the interval, calculates the RPM, and resets the edge count for the next
 * interval. If no edges are detected (indicating the fan is stopped), it turns
 * on a red LED.
 *
 *
 */
void timer1_callback();




/**
 * Initializes the fan speed measurement module.
 *
 * This function configures the necessary hardware for measuring the fan speed,
 * including setting up INT6 for interrupt on rising edge detection and
 * configuring Timer1 for periodic interrupts. It also sets the
 * `timer1_callback` function as the Timer1 callback.
 *
 * 
 */
void fanspeed_init(void);


/**
 * Gets the most recent fan speed measurement.
 *
 * @return     The most recent fan speed in RPM.
 *
 * This function returns the most recent fan speed calculated by the
 * `timer1_callback` function. 
 */
uint16_t fanspeed_getRecent(void);




/**
 * Gets the filtered fan speed using a median filter.
 *
 * @return     The median fan speed in RPM from the recent measurements.
 *
 * This function calculates and returns the median of the recent fan speed
 * measurements stored in a buffer. It uses a median filter to smooth out
 * fluctuations and provides a more stable speed reading. 
 */
uint16_t fanspeed_getFiltered(void);


#endif // SES_FANSPEED_H
