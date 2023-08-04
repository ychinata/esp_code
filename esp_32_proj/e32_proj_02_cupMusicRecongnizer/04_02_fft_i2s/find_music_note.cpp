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
 
extern int freqNormData[OLED_PIXEL_W];  //x����
extern SSD1306Wire oled;

// Ѱ������׷�
void NOTE_FindMaxNum(int* maxx, int* maxy)
{
    int maxtmpx = 0;
    int maxtmpy = 0;
    int startx = 10; // ���ݹ۲죬���������Ļ10���㣬��Ƶ��������
    for (int i = startx; i < OLED_PIXEL_W; i++) {
        if (freqNormData[i] > maxtmpy) {
            maxtmpy = freqNormData[i];
            maxtmpx = i;
        }
    }
    *maxx = maxtmpx;
    *maxy = maxtmpy;
    Serial.println("maxx"); 
    Serial.println(maxtmpx);        
}

// Ѱ�ҵڶ��׷�


void NOTE_Show(void)
{
    char str[20];
    int maxx = 1, maxy;
    int freqno;
    
    NOTE_FindMaxNum(&maxx, &maxy);
    freqno = maxx;
    sprintf(str, "FreqNo:%d", freqno);    
    oled.clear(); 
    oled.setFont(ArialMT_Plain_16);     // ��������
    oled.drawString(0, 48, str);    
    oled.display();        
}

