#ifndef SES_USBSERIAL_H_
#define SES_USBSERIAL_H_

/*INCLUDES-------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>

/*EXTERNALS------------------------------------------------------------------*/

/**
 * File descriptor for serial connection. You can use this in conjunction with fprintf.
 * Example fprintf(serialout, "Hello World %d\n",2023);
 */
extern FILE * serialout;


/*PROTOTYPES-----------------------------------------------------------------*/

/**
 * Initializes USB serial connection. 
 */
void usbserial_init();

/**
 * 
 */
void usbserial_update();

/**
 * Writes a character to UART.
 * @param chr character to write
 */
void usbserial_putc(uint8_t chr);

/**
 *	Reads a character from UART.
 *	@return character
 */
// uint8_t usbserial_getc(void); // TODO


#endif /* SES_USBSERIAL_H_ */