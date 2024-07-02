#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

/* DEFINES & MACROS ********************/

// ADC wiring on SES board
#define ADC_PORT_F         	PORTF
#define ADC_DDR_F           DDRF
#define ADC_CHANNEL_LIGHT   0
#define ADC_CHANNEL_POTI    6
#define ADC_CHANNEL_TEMP    7
#define ADC_INVALID_CHANNEL 0xFFFF

#define POWER_REDUCTION_REG PRR0
#define POWER_REDUCTION_ADC 0

#define ADMUX_REG           ADMUX
#define ADMUX_REFS0         6
#define ADMUX_REFS1         7
#define ADMUX_ADLAR         5
#define ADMUX0              0

#define ADC_PRESCALE        ADCSRA
#define ADPS0               0
#define ADPS1               1
#define ADPS2               2
#define ADEN                7
#define ADATE               5
#define ADSC                6

#define ADC_HIGH            ADCH
#define ADC_LOW             ADCL
#define ADC_REG             ADC

#define ADC_TEMP_RAW_LOW    852 //ADC VALUE FOR TEMP_LOW
#define ADC_TEMP_RAW_HIGH   549 //ADC VALUE FOR TEMP_HIGH
#define ADC_TEMP_HIGH       303 //KELVIN HIGH
#define ADC_TEMP_LOW        283 //KELVIN LOW

/* FUNCTION DECLARATIONS *******************/

void adc_init(void);
uint16_t adc_read(uint8_t adc_channel);
int16_t adc_getTemperature(void);

#endif // ADC_H
