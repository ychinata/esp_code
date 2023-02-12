/*
 https://www.bilibili.com/read/cv13525360
 2023.1.2 creat
 2023.1.15 换了两块屏幕后成功
 */
#include <SPI.h>
#include <TFT_eSPI.h>


/*

[TFT-- ESP32]
SCL -- IO18/SCK
SDA -- IO23/MOSI
RES -- IO26/D3
DC  -- IO25/D2
CS  -- IO27/D4

*/

/*

[SD -- ESP32]
SCL -- IO18/SCK
MISO-- IO19/MISO
SDA -- IO23/MOSI
CS  -- IO5

*/

TFT_eSPI tft = TFT_eSPI();

void setup(){
    // put your setup code here, to run once:
    tft.init();                     //初始化
    tft.fillScreen(TFT_GREEN);      //屏幕颜色
    tft.setCursor(10,10,1);         //设置起始坐标(10, 10)，2 号字体
    tft.setTextColor(TFT_WHITE);    //设置文本颜色为白色
    tft.setTextSize(2);             //设置文字的大小 (1~7)
    tft.println("TFT_Test");        //显示文字

    tft.fillCircle(30,40,10,TFT_BLUE);  //画圆
    tft.fillCircle(98,40,10,TFT_BLUE);  //画圆
    tft.drawLine(30,60,98,60,TFT_WHITE);//画线
    // 0.96 inch
//    tft.fillCircle(20,40,10,TFT_BLUE);  //画圆
//    tft.fillCircle(60,40,10,TFT_BLUE);  //画圆
//    tft.drawLine(15,60,65,60,TFT_WHITE);//画线
    
    tft.setTextColor(TFT_BLUE,TFT_BLUE);//设置文字颜色和背景颜色
    tft.setTextSize(1);
    tft.setCursor(40,80,1);             //设置起始坐标(10, 10)，2 号字体
    tft.println("ESP32");             //显示文字
    tft.setCursor(20,90,1);             //设置起始坐标(10, 10)，2 号字体
    tft.println("2023.1.16 by xy");             //显示文字       
}

void loop(){
    // put your main code here, to run repeatedly:
} 
