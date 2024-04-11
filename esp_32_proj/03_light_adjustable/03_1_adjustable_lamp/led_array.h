//#pragma once  
#ifndef __LED_ARRAY_H
#define __LED_ARRAY_H

#include <Arduino.h>
#include <analogWrite.h>

// IO config
// 高电平点亮
#define LED_PIN_G1 18
#define LED_PIN_R1 23
#define LED_PIN_B1 26
#define LED_PIN_G2 25
#define LED_PIN_R2 27
#define LED_PIN_B2 14

// 低电平点亮
#define LED_PIN_R3 33
#define LED_PIN_B3 32
#define LED_PIN_G3 14

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

void LED_Init(void);
void LED_TurnOnRgbAll(void);
void LED_TurnOffRgbAll(void);
void LED_TurnOnRgbOnBorad(void);
void LED_TurnOffRgbOnBorad(void);
void LED_SetAllKindofColorOnBorad(void);

#endif
