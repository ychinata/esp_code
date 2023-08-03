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
 *  The Electronic Engineer                                                                                                                              *                                                                                *
 *  github:    https://github.com/donnersm                                                                                                               *
 *                                                                                                                                                       *  
 ********************************************************************************************************************************************************/
#include "find_music_note.h"
#include "SSD1306Wire.h"    // 库管理器安装ESP8266 and ESP32 OLED diver for sSD1306 displays库，搜索esp8266-oled-ssd1306
#include "settings.h"

 
extern int freqNormData[FFT_FINDPEAK_W];  //x方向
extern SSD1306Wire oled;

// 寻找最大谱峰
void NOTE_FindMaxNum(int* maxx, int* maxy)
{
    int maxtmpx = 0;
    int maxtmpy = 0;

    for (int i = FIND_START; i < FFT_FINDPEAK_W; i++) {
        if (freqNormData[i] > maxtmpy) {
            maxtmpy = freqNormData[i];
            maxtmpx = i;
        }
    }
    *maxx = maxtmpx;
    *maxy = maxtmpy;
//    Serial.println("maxx"); 
//    Serial.println(maxtmpx);        
}

// 寻找第二谱峰
void NOTE_FindSecondNum(int* x, int* y, int maxx)
{
    //跳过最大谱峰± FFT_FIND_SKIP_NUM 的谱线
    int maxtmpx = 0;
    int maxtmpy = 0;
    
    int skip_left, skip_right;
    // 防止越界
    if (maxx + FFT_FIND_SKIP_NUM >= FFT_FINDPEAK_W) {
        skip_right = FFT_FINDPEAK_W - 1;
    } else {
        skip_right = maxx + FFT_FIND_SKIP_NUM;
    }
    // 左边从startx开始，不会越界
    skip_left = maxx - FFT_FIND_SKIP_NUM;
    
    
    for (int i = FIND_START; i < FFT_FINDPEAK_W; i++) {
        if (i >= skip_left && i <= skip_right) {
            continue;
        }
        if (freqNormData[i] > maxtmpy) {
            maxtmpy = freqNormData[i];
            maxtmpx = i;
        }
    }
    *x = maxtmpx;
    *y = maxtmpy;
//    Serial.println("maxx"); 
//    Serial.println(maxtmpx);      
}

int NOTE_FindMaxNo(void)
{
    char str[20], str2[20];
    int maxx, maxy, sndx, sndy;
    int xl, xh;	// xl是屏幕左边的点,对应较低频
    
    NOTE_FindMaxNum(&maxx, &maxy);
    NOTE_FindSecondNum(&sndx, &sndy, maxx);        
    
    // 比较大小
    if (maxx > sndx) {
        xh = maxx;
        xl = sndx;
    } else {
        xh = sndx;
        xl = maxx;
    }
    
    sprintf(str, "FreqNo:%d,%d", xl, xh);    
	sprintf(str2, "Max:%d", maxx);
    oled.clear(); 
    oled.setFont(ArialMT_Plain_16);     // 设置字体
    oled.drawString(0, OLED_FONT16_LINE_3, str);    	// 显示在第三行, 最大的两个频点并排序
    oled.drawString(0, OLED_FONT16_LINE_4, str2);    	// 显示在第四行, 最大的频点
    oled.display();        
    Serial.println(str);
	return maxx;
}

