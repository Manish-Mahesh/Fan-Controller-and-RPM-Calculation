/* INCLUDES ******************************************************************/

#include <avr/io.h>
#include "ses_led.h"

/* DEFINES & MACROS **********************************************************/

// LED wiring on SES board
#define LED_RED_PORT       	PORTF
#define LED_RED_DDR         DDRF
#define LED_RED_BIT         5

#define LED_GREEN_PORT      PORTD
#define LED_GREEN_DDR       DDRD
#define LED_GREEN_BIT       2

#define LED_YELLOW_PORT     PORTD
#define LED_YELLOW_DDR      DDRD
#define LED_YELLOW_BIT      3


/* FUNCTION DEFINITION *******************************************************/

void led_redInit(void) {
LED_RED_DDR |= (1<<LED_RED_BIT);
}

void led_redToggle(void) {
LED_RED_PORT ^= (1 << LED_RED_BIT);
}

void led_redOn(void) {
LED_RED_PORT &= ~(1<<LED_RED_BIT);
}

void led_redOff(void) {
LED_RED_PORT |= (1<<LED_RED_BIT);
}

void led_yellowInit(void) {
LED_YELLOW_DDR |= (1<<LED_YELLOW_BIT);
}

void led_yellowToggle(void) {
LED_YELLOW_PORT ^= (1 << LED_YELLOW_BIT);
}

void led_yellowOn(void) {
LED_YELLOW_PORT &= ~(1<<LED_YELLOW_BIT);
}

void led_yellowOff(void) {
LED_YELLOW_PORT |= (1<<LED_YELLOW_BIT);
}

void led_greenInit(void) {
LED_GREEN_DDR |= (1<<LED_GREEN_BIT);
}

void led_greenToggle(void) {
LED_GREEN_PORT ^= (1 << LED_GREEN_BIT);
}

void led_greenOn(void) {
LED_GREEN_PORT &= ~(1<<LED_GREEN_BIT);
}

void led_greenOff(void) {
LED_GREEN_PORT |=  (1<<LED_GREEN_BIT);
}
