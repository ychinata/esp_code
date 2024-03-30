 #ifndef __ROTARY_ENCODER_H
#define __ROTARY_ENCODER_H

#include <Arduino.h>

#define encoderPinA 23
#define encoderPinB 26

// internal
void ROTARYENCODER_INTA();
void ROTARYENCODER_INTB();
// external
void ROTARYENCODER_Init(void);
void ROTARYENCODER_Show(void);
double ROTARYENCODER_GetData(void);

#endif