//#pragma once  
#ifndef __KEY_H
#define __KEY_H

#include <Arduino.h>

#define KEY1_PIN 12        //按键所接的GPIO口
#define KEY2_PIN 4
#define KEY3_PIN 16
#define KEY4_PIN 17

int KEY_Init(void);
int KEY_IsPressDown(void);
int KEY_GetValue(void);

#endif
