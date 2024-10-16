//#pragma once  
#ifndef __KEY_H
#define __KEY_H

#include <Arduino.h>

// 引脚冲突（同时定义了输入输出?），会导致初始化卡住，OLED停在开机画面
#define KEY1_PIN 5        //KEY1与PWMA复用按键所接的GPIO口
#define KEY2_PIN 5         // KEY2(D25)与AIN1复用
#define KEY3_PIN 27
#define KEY4_PIN 5         

int KEY_Init(void);
int KEY_IsPressDown(void);
int KEY_GetValue(void);

#endif
