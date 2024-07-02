// /*
// #ifndef SES_BUTTON_H_
// #define SES_BUTTON_H_

// /* INCLUDES ******************************************************************/

// #include <stdbool.h>

// /* FUNCTION PROTOTYPES *******************************************************/

// /**
//  * Initializes rotary encoder button and pushbutton
//  */
// void button_init(void);

// /** 
//  * Get the state of the pushbutton.
//  */
// bool button_isPushButtonPressed(void);

// /** 
//  * Get the state of the rotary button.
//  */
// bool button_isRotaryButtonPressed(void);


// #endif /* SES_BUTTON_H_ */

// */

#ifndef SES_BUTTON_H_
#define SES_BUTTON_H_

/* INCLUDES ******************************************************************/
#include <stdbool.h>
void button_init(bool debouncing);
/* FUNCTION PROTOTYPES *******************************************************/

/**
 * Initializes rotary encoder button and pushbutton
 */


/** 
 * Get the state of the pushbutton.
 */
bool button_isPushButtonPressed(void);

/** 
 * Get the state of the rotary button.
 */
bool button_isRotaryButtonPressed(void);

/** 
 * Typedef for the button callback function pointer
 */
typedef void (*pButtonCallback)(void);

/**
 * Set the callback function for the rotary button
 */
void button_setRotaryButtonCallback(pButtonCallback callback);

/**
 * Set the callback function for the push button
 */
void button_setPushButtonCallback(pButtonCallback callback);
void button_checkState(void);

#endif /* SES_BUTTON_H_ */
