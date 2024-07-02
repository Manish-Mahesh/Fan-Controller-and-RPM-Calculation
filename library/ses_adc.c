#include "ses_adc.h"

void adc_init(void) {
    /* Clearing DDRF bits 0,6,7 to make ADC channels as Inputs */
    ADC_DDR_F = (ADC_DDR_F & ~(1 << ADC_CHANNEL_LIGHT)) |
                (ADC_DDR_F & ~(1 << ADC_CHANNEL_TEMP)) |
                (ADC_DDR_F & ~(1 << ADC_CHANNEL_POTI));

    /* Disabling the Pull-ups for the PORTF Pins and ADC channels */
    ADC_PORT_F = (ADC_PORT_F & ~(1 << ADC_CHANNEL_LIGHT)) |
                 (ADC_PORT_F & ~(1 << ADC_CHANNEL_TEMP)) |
                 (ADC_PORT_F & ~(1 << ADC_CHANNEL_POTI));

    /* Disabling the ADC Power Reduction Mode in PRR0 Register */
    POWER_REDUCTION_REG &= ~(1 << POWER_REDUCTION_ADC);

    /* Disabling Internal Vref and Selecting External AVREF + Right Adjust */
    ADMUX_REG = (ADMUX_REG & ~(1 << ADMUX_REFS0)) |
                (ADMUX_REG & ~(1 << ADMUX_REFS1)) |
                (ADMUX_REG & ~(1 << ADMUX_ADLAR));

    /* Enabling ADC and Disabling Auto Triggering */
    ADC_PRESCALE = (ADC_PRESCALE | (1 << ADEN)) |
                   (ADC_PRESCALE & ~(1 << ADATE));

    /* 10 Bit Resolution for 16MHz Clock- Set Prescale to CK/128 */
    ADC_PRESCALE = (ADC_PRESCALE | (1 << ADPS0)) |
                   (ADC_PRESCALE | (1 << ADPS1)) |
                   (ADC_PRESCALE | (1 << ADPS2));
}

uint16_t adc_read(uint8_t adc_channel) {
    switch (adc_channel) {
        case ADC_CHANNEL_LIGHT:
            ADMUX_REG = (ADMUX_REG & ~(1 << ADMUX0)) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 1))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 2))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 3))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 4)));
            ADC_PRESCALE |= (1 << ADSC);
            while ((ADC_PRESCALE & (1 << ADSC))) {
                ;
            }
            return ADC;
        case ADC_CHANNEL_TEMP:
            ADMUX_REG = (ADMUX_REG | (1 << ADMUX0)) |
                        (ADMUX_REG | (1 << (ADMUX0 + 1))) |
                        (ADMUX_REG | (1 << (ADMUX0 + 2))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 3))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 4)));
            ADC_PRESCALE |= (1 << ADSC);
            while ((ADC_PRESCALE & (1 << ADSC))) {
                ;
            }
            return ADC;
        case ADC_CHANNEL_POTI:
            ADMUX_REG = (ADMUX_REG & ~(1 << ADMUX0)) |
                        (ADMUX_REG | (1 << (ADMUX0 + 1))) |
                        (ADMUX_REG | (1 << (ADMUX0 + 2))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 3))) |
                        (ADMUX_REG & ~(1 << (ADMUX0 + 4)));
            ADC_PRESCALE |= (1 << ADSC);
            while ((ADC_PRESCALE & (1 << ADSC))) {
                ;
            }
            return ADC;
        default:
            return ADC_INVALID_CHANNEL;
    }
}

int16_t adc_getTemperature(void) {
    int32_t adc = adc_read(ADC_CHANNEL_TEMP);
    return (int16_t)(((adc - ADC_TEMP_RAW_LOW) * (ADC_TEMP_HIGH - ADC_TEMP_LOW)) /
                     (ADC_TEMP_RAW_HIGH - ADC_TEMP_RAW_LOW)) + ADC_TEMP_LOW;
}
