//#pragma once  
#ifndef _OLED_I2C_ADAFRUIT_H
#define _OLED_I2C_ADAFRUIT_H

#include <Arduino.h>

// On an arduino UNO/NANO:   A4(SDA), A5(SCL)
// On an arduino MEGA 2560:  20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // 0.96寸64, 0.91寸32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // See datasheet for Address:3C/3D

void OLED_I2C_Adafruit_Init(void);
void OLED_I2C_Adafruit_DrawStrShow(int x, int y, char* str, int size);
void OLED_I2C_Adafruit_DrawStr(int x, int y, char* str, int size);
void OLED_ClearDisplay(void);
void OLED_SetDisplay(void);

//test
void OLED_I2C_Adafruit_DrawStrSize2Test(void);

#endif