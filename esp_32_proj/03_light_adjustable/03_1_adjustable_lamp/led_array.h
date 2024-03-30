//#pragma once  
#ifndef __LED_ARRAY_H
#define __LED_ARRAY_H

#include <Arduino.h>
#include <analogWrite.h>

// IO config
#define LED_PIN_G1 18   // D5
#define LED_PIN_R1 23   // D5
#define LED_PIN_B1 26   // D5
#define LED_PIN_G2 25   // D5
#define LED_PIN_R2 27   // D5

#define LED_PIN_COLD 27
#define LED_PIN_WARM 25

void LED_SetPinPwm(int ledPin, int pwmValue);
void LED_SetPinBlink(int ledPin);
void LEDARRAY_Set(int secound_int);

void LED_TurnOff(void);
void LED_TurnOnWarm(int ledPwmValue);
void LED_TurnOnCold(int ledPwmValue);
void LED_TurnOn(void);
void LED_TurnOnLevel(int ledPwmValue);

#endif
