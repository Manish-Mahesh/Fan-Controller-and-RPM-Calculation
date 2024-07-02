/* INCLUDES ******************************************************************/
#include <stdlib.h>
#include <avr/interrupt.h>
#include "ses_timer.h"


/* DEFINES & MACROS **********************************************************/
#define TIMER0_CYC_FOR_1MILLISEC (F_CPU / 64 / 1000) // Assuming prescaler of 64
#define TIMER1_CYC_FOR_5MILLISEC (F_CPU / 64 / 200)  // Assuming prescaler of 64
#define TIMER3_CYC_FOR_1MILLISEC (F_CPU / 64 / 1000) // Assuming prescaler of 64
#define TIMER1_CYC_FOR_1SECOND   (F_CPU / 256) 
/* FUNCTION POINTERS *********************************************************/
static pTimerCallback timer0_callback;
static pTimerCallback timer1_callback;

/* FUNCTION DEFINITIONS ******************************************************/
void timer0_setCallback(pTimerCallback cb) {
    timer0_callback = cb;
}

void timer0_start() {
    // Configure Timer0 for CTC modeF
    TCCR0A |= (1 << WGM01);  // CTC mode
    TCCR0B |= (1 << CS01) | (1 << CS00);  // Prescaler 64

    // Set the compare value for 1ms
    OCR0A = TIMER0_CYC_FOR_1MILLISEC;

    // Enable Output Compare Match A Interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Reset Timer
    TCNT0 = 0;
    sei();
}

void timer0_stop() {
    // Disable Output Compare Match A Interrupt
    TIMSK0 &= ~(1 << OCIE0A);

    // Stop the timer
    TCCR0B &= ~((1 << CS01) | (1 << CS00));
}

void timer1_setCallback(pTimerCallback cb) {
    timer1_callback = cb;
}

void timer1_start() {
    // Configure Timer1 for CTC mode
    TCCR1B |= (1 << WGM12);  // CTC mode
    TCCR1B |= (1 << CS12);  // Prescaler 256

    // Set the compare value for 5ms
    OCR1A = TIMER1_CYC_FOR_1SECOND;

    // Enable Output Compare Match A Interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Reset Timer
    TCNT1 = 0;
}

void timer1_stop() {
    // Disable Output Compare Match A Interrupt
    TIMSK1 &= ~(1 << OCIE1A);

    // Stop the timer
    TCCR1B &= ~((1 << CS11) | (1 << CS10));
}

ISR(TIMER0_COMPA_vect) {
    if (timer0_callback != NULL) {
        timer0_callback();
    }
}

ISR(TIMER1_COMPA_vect) {
    if (timer1_callback != NULL) {
        timer1_callback();
    }
}


