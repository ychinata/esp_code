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


/* 设置参数-end */

// FFT寻峰参数
// 用128点太粗糙, 考虑用512点
#define FIND_PEAK_SCALE_FACTOR 4	// 512是128的四倍
#define FFT_FINDPEAK_H 64		//
#define FFT_FINDPEAK_W 512		// FFT寻峰用的点数,可以映射到OLED的128点
#define FFT_FIND_SKIP_NUM (10*FIND_PEAK_SCALE_FACTOR)		//跳过最大谱峰± FFT_FIND_SKIP_NUM 的谱线
#define FIND_START (20*FIND_PEAK_SCALE_FACTOR)  // 依据观察，跳过左边屏幕x个点，低频干扰严重


const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */

//OLED宏定义
#define OLED_FONT16_LINE_1	0
#define OLED_FONT16_LINE_2	16
#define OLED_FONT16_LINE_3	32
#define OLED_FONT16_LINE_4	48

#endif
