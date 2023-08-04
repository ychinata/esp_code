 /********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *  Project:         Webspector - WebServer based Spectrum Analyzer                                                                                      *
 *  Target Platform: ESP32                                                                                                                               *
 *                                                                                                                                                       * 
 *  Version: 1.0                                                                                                                                         *
 *  Hardware setup: See github                                                                                                                           *
 *                                                                                                                                                       *
 *                                                                                                                                                       * 
 *  Mark Donners                                                                                                                                         *
 *  The Electronic Engineer                                                                                                                              *
 *  Website:   www.theelectronicengineer.nl                                                                                                              *
 *  facebook:  https://www.facebook.com/TheelectronicEngineer                                                                                            *
 *  youtube:   https://www.youtube.com/channel/UCm5wy-2RoXGjG2F9wpDFF3w                                                                                  *
 *  github:    https://github.com/donnersm                                                                                                               *
 *                                                                                                                                                       *  
 ********************************************************************************************************************************************************/
 

#ifndef __SETTINGS_H__
#define __SETTINGS_H__ 	

#define MODE_BUTTON_PIN     0


/* 设置oled屏幕的相关信息 */
#define SDA_PIN 21                       // SDA引脚
#define SCL_PIN 22                       // SCL引脚

// OLED
#define OLED_PIXEL_H 64
#define OLED_PIXEL_W 128


const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */



// 存储屏幕像素点x,y用于寻找频点
#endif
