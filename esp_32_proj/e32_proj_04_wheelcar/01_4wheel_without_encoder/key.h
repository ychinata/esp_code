//#pragma once  
#ifndef __KEY_H
#define __KEY_H

#include <Arduino.h>

#define KEY1_PIN 35        //按键所接的GPIO口
#define KEY2_PIN 34

int KEY_Init(void);
int KEY_IsPressDown(void);
void Key_SetMoterState(void);
int Key_GetMoterState(void);
int KEY_IsPressDown(void);

#endif
