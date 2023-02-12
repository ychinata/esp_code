/*
 https://www.bilibili.com/read/cv13525360
 2023.1.2
 */
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup(){
    // put your setup code here, to run once:
    tft.init();                     //初始化
    tft.fillScreen(TFT_YELLOW);      //屏幕颜色
    tft.setCursor(10,10,1);         //设置起始坐标(10, 10)，2 号字体
    tft.setTextColor(TFT_WHITE);    //设置文本颜色为白色
    tft.setTextSize(2);             //设置文字的大小 (1~7)
    tft.println("TFT_Test");        //显示文字
    tft.fillCircle(30,40,10,TFT_BLUE);  //画圆
    tft.fillCircle(98,40,10,TFT_BLUE);  //画圆
    tft.drawLine(30,60,98,60,TFT_WHITE);//画线
    tft.setTextColor(TFT_BLUE,TFT_BLUE);//设置文字颜色和背景颜色
    tft.setCursor(40,80,1);             //设置起始坐标(10, 10)，2 号字体
    tft.setTextSize(1);
    tft.println("ESP8266");             //显示文字
    tft.setCursor(20,90,1);             //设置起始坐标(10, 10)，2 号字体
    tft.println("2023.1.16 by xy");             //显示文字    
}

void loop(){
    // put your main code here, to run repeatedly:
} 
