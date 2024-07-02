#include "ses_fanspeed.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ses_led.h"
#include "ses_timer.h"
#include <util/atomic.h>
#include <string.h>
#include "ses_display.h"

#define MEDIAN_FILTER_SIZE 5

static volatile uint16_t edge_count = 0;


static uint16_t speed_samples[MEDIAN_FILTER_SIZE] = {0};
static uint8_t sample_index = 0;
// static uint8_t is_initialized = 0; //To check if the buffer is full with values
static uint16_t rpm = 0;



void fanspeed_init(void) {
    // Enable INT6 (interrupt on a rising edge)
    EICRB |= (1 << ISC61) | (1 << ISC60);
    EIMSK |= (1 << INT6);

    timer1_setCallback(timer1_callback);

    // Start Timer1 (1 sec callback)
    timer1_start();
}

void timer1_callback() {
   
    
    uint16_t current_edge_count;
    
    
    led_greenToggle();  // To check this function (callback) is called every 1sec
    
    display_setCursor(0, 7);
    
    fprintf(displayout, "Edges:-  %d per second  ", edge_count);
    
    display_update();
    
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        current_edge_count = edge_count;
        edge_count = 0;
    }
    
    rpm = (current_edge_count) * 30;
  // Insert the current speed into the sample buffer
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        speed_samples[sample_index++] = rpm;
        if (sample_index >= MEDIAN_FILTER_SIZE) {
            sample_index = 0;
           // is_initialized = 1;  // to update if the buffer is full
        }
    }
    // Turn on the red LED if the fan stops
    if (rpm == 0) {
        led_redOn();
    } else {
        led_redOff();
    }
}

ISR(INT6_vect) {
    edge_count++;
    led_yellowToggle();
}

uint16_t fanspeed_getRecent(void) {
    uint16_t speed;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        speed = rpm;
    }
    return speed;
}

uint16_t fanspeed_getFiltered(void) {
    uint16_t sorted[MEDIAN_FILTER_SIZE];
    
    // Copy the samples array outside of the atomic block
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        memcpy(sorted, speed_samples, MEDIAN_FILTER_SIZE * sizeof(uint16_t));
    }

    // Sort the samples
    for (uint8_t i = 0; i < MEDIAN_FILTER_SIZE - 1; i++) {
        for (uint8_t j = 0; j < MEDIAN_FILTER_SIZE - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                uint16_t temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    // Return the median value

    return  sorted[MEDIAN_FILTER_SIZE / 2];

    //return is_initialized ? sorted[MEDIAN_FILTER_SIZE / 2] : rpm;  // returning the median value only if the buffer was full
}
