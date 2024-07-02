


#include "ses_fan.h"
#include <avr/io.h>


void fan_init(void) {
    // Set PD4 as output for controlling the fan power supply
    DDRD |= (1 << PD4);
    DDRC |= (1 << PC6);
    // Enable Timer3 by clearing the Power Reduction Timer/Counter3 bit
    PRR1 &= ~(1 << PRTIM3);

    // Set Fast PWM mode with 8-bit resolution
    TCCR3A = (1 << WGM30) | (1 << COM3A1); // WGM30 for Fast PWM, COM3A1 for non-inverting mode
    TCCR3B = (1 << WGM32) | (1 << CS32);  // WGM32 for Fast PWM, CS31 for prescaler 8

    // Initialize OCR3A to 0 (0% duty cycle)
    OCR3A = 0;
}




void fan_enable(void) {
    
    PORTD |= (1 << PD4);  //Enable Fan
}

void fan_disable(void) {
    // Disable fan and set duty cycle to 0
    PORTD &= ~(1 << PD4);
    OCR3A = 0;
}


void fan_setDutyCycle(uint8_t dc) {
    // Set PWM duty cycle by adjusting OCR3A
   
    OCR3A = dc;
    
    

}
