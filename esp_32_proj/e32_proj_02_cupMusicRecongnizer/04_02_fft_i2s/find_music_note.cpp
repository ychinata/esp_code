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
#include "find_music_note.h"
#include "SSD1306Wire.h"    // ���������װESP8266 and ESP32 OLED diver for sSD1306 displays�⣬����esp8266-oled-ssd1306
#include "settings.h"

#define FIND_START 20  // ���ݹ۲죬���������Ļx���㣬��Ƶ��������
 
extern int freqNormData[OLED_PIXEL_W];  //x����
extern SSD1306Wire oled;

// Ѱ������׷�
void NOTE_FindMaxNum(int* maxx, int* maxy)
{
    int maxtmpx = 0;
    int maxtmpy = 0;

    for (int i = FIND_START; i < OLED_PIXEL_W; i++) {
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

// Ѱ�ҵڶ��׷�
void NOTE_FindSecondNum(int* x, int* y, int maxx)
{
    //��������׷��3������
    int maxtmpx = 0;
    int maxtmpy = 0;
    
    int skip_left, skip_right;
    // ��ֹԽ��
    if (maxx + 3 >= 128) {
        skip_right = 127;
    } else {
        skip_right = maxx + 3;
    }
    // ��ߴ�startx��ʼ������Խ��
    skip_left = maxx - 3;
    
    
    for (int i = FIND_START; i < OLED_PIXEL_W; i++) {
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

void NOTE_Show(void)
{
    char str[20];
    int maxx, maxy, sndx, sndy;
    
    NOTE_FindMaxNum(&maxx, &maxy);
    NOTE_FindSecondNum(&sndx, &sndy, maxx);        
    
    sprintf(str, "FreqNo:%d,%d", maxx, sndx);    
    oled.clear(); 
    oled.setFont(ArialMT_Plain_16);     // ��������
    oled.drawString(0, 48, str);    
    oled.display();        
    Serial.println(str);
}

//20230804 ��, 1024fft, 10kHz
/*
200ml:27/68
180ml:30/74
160ml:33/81
140ml:34/85
120ml:36/91
100ml:37/95
80ml :39/102
60ml :40/108
40ml :40/109
0ml  :38/105

*/