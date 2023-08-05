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


/* 设置引脚-begin */
#define SDA_PIN 21                       // SDA引脚
#define SCL_PIN 22                       // SCL引脚
/* 设置引脚-end */

/* 设置参数-begin */
// 采样率
#define FFT_SMP_RATE 6000  // 10k谱线在屏幕中间靠左

#define FFT_AMP_ATTEN_FACTOR 10     // 幅值衰减因子.ADC时为100效果可以.INMP441用10效果可以
#define FFT_TIMEAMP_ATTEN_FACTOR 1000     // 幅值衰减因子.ADC时为100效果可以.INMP441用1000效果可以

#define FFT_FIND_SKIP_NUM 10		//跳过最大谱峰± FFT_FIND_SKIP_NUM 的谱线
#define FIND_START 20  // 依据观察，跳过左边屏幕x个点，低频干扰严重


/* 设置参数-end */

// OLED
#define OLED_PIXEL_H 64
#define OLED_PIXEL_W 128


const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */



#endif
