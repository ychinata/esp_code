//#pragma once  
#ifndef __LED_ARRAY_H
#define __LED_ARRAY_H

#include <Arduino.h>
#include <analogWrite.h>

void LED_SetPinPwm(int ledPin, int pwmValue);
void LED_SetPinBlink(int ledPin);
void LEDARRAY_Set(int secound_int);

#endif
