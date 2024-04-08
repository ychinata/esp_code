/********************************************
 *@File: 0.91/0.96寸OLED滚动显示(使用Adafruit库)
        需要安装三个库：Adafruit_BusIO、Adafruit_GFX_Library、Adafruit_SSD1306
 *@Author: Cseexy
 *@Date: 2024.2.11
 *@Description: SDA<->A4
                SCL<->A5
 *********************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "oled_i2c_adafruit.h"

#define PX2 12  // pixels_x for fontsize2
#define PY2 16  // pixels_y for fontsize2

// OLED对象初始化
Adafruit_SSD1306 OledObj(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void OLED_I2C_Adafruit_Init(void) {
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!OledObj.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // 显示开机Adafruit画面(在初始buffer里)
    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    OledObj.display();
    delay(500); // Pause for 2 seconds
    // Clear the buffer
    OledObj.clearDisplay();
    // 显示开机Adafruit画面end    
    OledObj.setTextColor(WHITE);    //开像素点发光
}

void OLED_I2C_Adafruit_DrawStrShow(int x, int y, char* str, int size) {
    OledObj.clearDisplay();         //清屏
    OledObj.setTextSize(size); //设置字体大小
    OledObj.setCursor(x, y);//设置显示位置
    OledObj.println(str);
    OledObj.display(); // 开显示
}

void OLED_I2C_Adafruit_DrawStr(int x, int y, char* str, int size) {
    OledObj.setTextSize(size); //设置字体大小
    OledObj.setCursor(x, y);//设置显示位置
    OledObj.println(str);
}

// 维测函数
// size2:每个字符占12*16个像素
void OLED_I2C_Adafruit_DrawStrSize2Test(void) {
    int fontsize = 2;
    OLED_ClearDisplay();    
    OLED_I2C_Adafruit_DrawStr(0*PX2, 0*PY2, "123456789A", fontsize);  //第1行,第1列
    OLED_I2C_Adafruit_DrawStr(2*PX2, 1*PY2, "12345678", fontsize);    //第2行,第3列
    OLED_I2C_Adafruit_DrawStr(2*PX2, 2*PY2, "TonyCode", fontsize);    //第3行,第3列
    OLED_I2C_Adafruit_DrawStr(3*PX2, 3*PY2, "2024215", fontsize);     //第4行,第4列
    OLED_SetDisplay();
}

void OLED_ClearDisplay(void) {
    OledObj.clearDisplay();         //清屏
}

void OLED_SetDisplay(void) {
    OledObj.display(); // 开显示
}