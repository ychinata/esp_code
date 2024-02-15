#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2     //硬件I2C
(U8G2_R0, 
SCL,    /* clock=*/ 
SDA,    /* data=*/  
U8X8_PIN_NONE /* reset=*/); // 没有重置显示的所有板

void setup() {
    Serial.begin(115200);
    u8g2.setBusClock(800000);     //设置时钟
    u8g2.begin();//初始化
    u8g2.enableUTF8Print();       //允许UTF8
}

void loop() {
    static unsigned int start = millis();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB12_tr);        //设定字体
    u8g2.drawStr(0, 13, "Hello World!");       //在指定位置显示字符串

    u8g2.setFont(u8g2_font_wqy14_t_gb2312b);   //换成中文字体
    u8g2.setCursor(0, 30);
    u8g2.print("你不要过来啊！");
    //u8g2.drawUTF8(0, 50, "呵呵");
    u8g2.drawUTF8(0, 60, "U8g2首秀2.15");

    u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
    u8g2.drawGlyph(90,60,0x0045);
    u8g2.sendBuffer();
    static unsigned int end = millis();
    Serial.println(end-start);
}
