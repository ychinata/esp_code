
/*
 * ESP8266-NodeMCU通过驱动oled显示文文字和图片
 * 需要使用Arduino-OLED第三方库：https://github.com/ThingPulse/esp8266-oled-ssd1306/tree/4.2.0
 * 参考：https://www.bilibili.com/video/BV1v44y1J7Cb
 */
//2023.1.6

/* 使用0.96寸的OLED屏幕需要使用包含这个头文件 */
#include "SSD1306Wire.h"

/* 设置oled屏幕的相关信息 */
const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
#define SDA_PIN 21                       // SDA引脚，默认gpio4
#define SCL_PIN 22                       // SCL引脚，默认gpio5

/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);


void setup() {
    /* 1. 初始化串口通讯波特率为115200*/
    Serial.begin(115200);
    
    /* 2. oled屏幕初始化 */
    oled.init();
    oled.flipScreenVertically();        // 设置屏幕翻转
    oled.setContrast(255);              // 设置屏幕亮度
    drawRect();                         // 测试屏幕显示
    oled.clear(); 
    oled.display();       // 清除屏幕
}

void loop() {
    // oled.setFont(ArialMT_Plain_24);     // 设置字体    
    oled.setFont(ArialMT_Plain_16);     // 设置字体
    oled.drawString(0, 0, "ESP32 Demo");     // 将要显示的文字写入缓存
    oled.drawString(0, 16, "I love STU!");
    oled.drawString(0, 32, "I love DGPT!");
    oled.drawString(0, 48, "2023.1.6");
    oled.display();                     // 将缓存里的文字在屏幕上显示
    //digitalWrite(LED_BUILTIN, LOW);     // Turn the LED on
    //delay(300);
    //digitalWrite(LED_BUILTIN, HIGH);    // Turn the LED off
    //delay(500);
}

void drawRect(void) {
    for (int16_t i=0; i<oled.getHeight()/2; i+=2) {
        oled.drawRect(i, i, oled.getWidth()-2*i, oled.getHeight()-2*i);
        oled.display();
        delay(50);
    }
}
