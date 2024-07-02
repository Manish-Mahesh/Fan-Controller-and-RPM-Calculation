#include "ses_scheduler.h"
#include "ses_led.h"
#include "ses_button.h"
#include "ses_display.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include "ses_fan.h"
#include "ses_adc.h"
#include "ses_timer.h"
#include "ses_fanspeed.h"


volatile uint8_t fanOn = 0; // Volatile for variable modified in ISR

// Task descriptors
static task_descriptor_t buttonCheckTask;
static task_descriptor_t potentiometerTask;
static task_descriptor_t fanSpeedDisplayTask; 


void fanSpeedDisplayTaskHandler(void *param) {
    uint16_t currentFanSpeed = fanspeed_getRecent();
    uint16_t filteredFanSpeed = fanspeed_getFiltered();
    
    display_setCursor(0, 3);
    fprintf(displayout, "Fan Speed: %d RPM  ", currentFanSpeed); // Print unfiltered fan speed on display
    display_setCursor(0, 5);
    fprintf(displayout, "Filtered Speed : %d RPM  ", filteredFanSpeed); // Print filtered fan speed on display
    display_update();

}





void buttonPressHandler(void) {
    fanOn = !fanOn; // Toggle fan state

    if (fanOn) {
        fan_enable(); // Turn on the fan
    } else {
        fan_disable(); // Turn off the fan
    }
}

void buttonCheckTaskHandler(void *param) {
    button_checkState(); // Check button state for debouncing
}

void potentiometerTaskHandler(void *param) {
    
    uint32_t potValue = adc_read(ADC_CHANNEL_POTI); // Read the potentiometer value and set the fan speed accordingly
    uint8_t dutyCycle = (uint8_t)((potValue * 255) / 1023); // Scale potentiometer value to 0-255
    fan_setDutyCycle(dutyCycle);

    // Update the display with potentiometer value and duty cycle

    display_setCursor(0, 0); // Set cursor to first row
    fprintf(displayout, "Pot: %ld  DutyCycle: %d  ", potValue,dutyCycle); // Print potentiometer value on display
    display_update();
}


int main() {
    fan_init();
    button_init(false); // Disable pin change interrupt and debounce check (debouncing check is called by scheduler)
    fanspeed_init();
    sei(); // Enable global interrupts
    timer0_start(); // Start timer0
    display_init();
    adc_init();
    led_yellowInit();
    led_redInit();
    led_greenInit();
    button_setPushButtonCallback(buttonPressHandler);

    //  Task descriptor for button state checking (debouncing)
    buttonCheckTask.task = buttonCheckTaskHandler;
    buttonCheckTask.param = NULL;
    buttonCheckTask.expire = 5; // 5 ms delay 
    buttonCheckTask.period = 5; // 5 ms period 
    buttonCheckTask.execute = 0;
    buttonCheckTask.next = NULL;

    // Task descriptor for potentiometer reading and displaying it. 
    potentiometerTask.task = potentiometerTaskHandler;
    potentiometerTask.param = NULL;
    potentiometerTask.expire = 100; // 100 ms delay 
    potentiometerTask.period = 100; // 100 ms period 
    potentiometerTask.execute = 0;
    potentiometerTask.next = NULL;

// Task descriptor for fan speed reading and displaying it.
    fanSpeedDisplayTask.task = fanSpeedDisplayTaskHandler;
    fanSpeedDisplayTask.param = NULL;
    fanSpeedDisplayTask.expire = 1000; // 1 second delay 
    fanSpeedDisplayTask.period = 1000; // 1 second period
    fanSpeedDisplayTask.execute = 0;
    fanSpeedDisplayTask.next = NULL;
    // Initialize the scheduler
    scheduler_init();

    // Add tasks to the scheduler
    scheduler_add(&buttonCheckTask);
    scheduler_add(&potentiometerTask);
    scheduler_add(&fanSpeedDisplayTask);
    // Run the scheduler
    scheduler_run();
    
    return 0; 
}
