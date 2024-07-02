


#include <avr/io.h> 
#include <avr/interrupt.h>
#include "ses_led.h"
#include "ses_button.h"
#include <stdlib.h>
#include "ses_timer.h"

#define BUTTON_ROTARY_PIN 5
#define BUTTON_PUSH_PIN 4
#define BUTTON_NUM_DEBOUNCE_CHECKS 5
#define BUTTON_DEBOUNCE_POS_PUSHBUTTON 0x01
#define BUTTON_DEBOUNCE_POS_ROTARYBUTTON 0x02

/* Static variables to store the callback functions */
static volatile pButtonCallback rotaryCallback = NULL;
static volatile pButtonCallback pushCallback = NULL;

void button_checkState() {
    static uint8_t state[BUTTON_NUM_DEBOUNCE_CHECKS] = { 0 };
    static uint8_t index = 0;
    static uint8_t debouncedState = 0;
    uint8_t lastDebouncedState = debouncedState;

    // each bit in every state byte represents one button
    state[index] = 0;
    if (button_isPushButtonPressed()) {
        state[index] |= BUTTON_DEBOUNCE_POS_PUSHBUTTON;
    }
    if (button_isRotaryButtonPressed()) {
        state[index] |= BUTTON_DEBOUNCE_POS_ROTARYBUTTON;
    }

    index++;
    if (index == BUTTON_NUM_DEBOUNCE_CHECKS) {
        index = 0;
    }

    // Init compare value and compare with ALL reads
    uint8_t j = 0xFF;
    for (uint8_t i = 0; i < BUTTON_NUM_DEBOUNCE_CHECKS; i++) {
        j = j & state[i];
    }
    debouncedState = j;

    // Callbacks for push button and rotary button
    if ((debouncedState & BUTTON_DEBOUNCE_POS_PUSHBUTTON) && !(lastDebouncedState & BUTTON_DEBOUNCE_POS_PUSHBUTTON)) {
        if (pushCallback != NULL) {
            pushCallback();
        }
    }
    if ((debouncedState & BUTTON_DEBOUNCE_POS_ROTARYBUTTON) && !(lastDebouncedState & BUTTON_DEBOUNCE_POS_ROTARYBUTTON)) {
        if (rotaryCallback != NULL) {
            rotaryCallback();
        }
    }
}

void button_init(bool debouncing) {
    // Configure the pins for the buttons as inputs
    DDRB &= ~(1 << BUTTON_ROTARY_PIN);
    DDRB &= ~(1 << BUTTON_PUSH_PIN);
    
    // Enable pull-up resistors
    PORTB |= (1 << BUTTON_ROTARY_PIN);
    PORTB |= (1 << BUTTON_PUSH_PIN);
    if (debouncing) {
        // Set up a timer to call button_checkState every 5ms
        // Assuming this function sets up Timer1
        timer1_setCallback(button_checkState);
        timer1_start();
    } 
    else
     {
        // Enable pin change interrupt for PCINT0 (Pin Change Interrupt Control Register)
        /*
        PCICR |= (1 << PCIE0);
        
        // Enable pin change interrupt for specific pins in the mask register
        PCMSK0 |= (1 << BUTTON_ROTARY_PIN);
        PCMSK0 |= (1 << BUTTON_PUSH_PIN);

        // Enable global interrupts
        //sei();
    
*/    }

}
    // Enable pin change interrupt for PCINT0 (Pin Change Interrupt Control Register)
    


bool button_isPushButtonPressed(void) {
    return (PINB & (1 << BUTTON_PUSH_PIN)) == 0;
}

bool button_isRotaryButtonPressed(void) {
    return (PINB & (1 << BUTTON_ROTARY_PIN)) == 0;
}

void button_setRotaryButtonCallback(pButtonCallback callback) {
    rotaryCallback = callback;
}

void button_setPushButtonCallback(pButtonCallback callback) {
    pushCallback = callback;
}

ISR(PCINT0_vect) {
   
        if ((PINB & (1 << BUTTON_PUSH_PIN)) == 0) {
            if (pushCallback != NULL) {
                pushCallback();
            }
        }
        
        // Check if the rotary button state changed and execute the callback if set
        if ((PINB & (1 << BUTTON_ROTARY_PIN)) == 0) {
            if (rotaryCallback != NULL) {
                rotaryCallback();
            }
        }
}
