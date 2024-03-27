/********************************************
 *@File: 基于ESP32的LED调光灯 
 *@Author: xxy
 *@Date: 2024.3.27
 *********************************************/
#include <Wire.h>
#include "bh1750.h"
#include "led_array.h"
//#include "oled_i2c_adafruit.h"
//#include "power_measure.h"
#include "rotary_encoder.h"

// IO config
#define LED_PIN_G1 18   // D5
#define LED_PIN_R1 23   // D5
#define LED_PIN_B1 26   // D5
#define LED_PIN_G2 25   // D5
#define LED_PIN_R2 27   // D5
//

void setup() {
    // 初始化
    Serial.begin(9600);
    BH1750_Init();                  //初始化BH1750
    //OLED_I2C_Adafruit_Init();  
    ROTARYENCODER_Init();  

    // 一路灯板D4
    pinMode(LED_PIN_G1, OUTPUT);
    pinMode(LED_PIN_R1, OUTPUT);
    pinMode(LED_PIN_B1, OUTPUT);
    pinMode(LED_PIN_G2, OUTPUT);
    pinMode(LED_PIN_R2, OUTPUT);                
    // key D8
    pinMode(8, INPUT);
}

void loop() {
    //Serial.println(lights);
    double brightValue = 0.0;
    int ledPwmValue = 0;
    int lux = 0;
    
    brightValue = ROTARYENCODER_GetData();          // 获取编码器设定的亮度值
    ledPwmValue = map(brightValue, 0, 360, 0, 255); // 将编码器原始值0-360映射到pwm值0-255,超出0-360的范围会重新映射
    //LED_SetPinPwm(LED_PIN, ledPwmValue);            // 调光
    // 点灯
    LED_LightWarm();
    LED_LightWhite();
    
    ROTARYENCODER_Show();       // 调光值维测
    //Serial.println(ledPwmValue);
    lux = BH1750_GetData();               // 获取光照强度数据
    //OLED_ShowBright(brightValue, ledPwmValue, lux);
}

void LED_LightWarm() {
  int ledPwmValue = 55;
  LED_SetPinPwm(LED_PIN_G2, ledPwmValue); 
  LED_SetPinPwm(LED_PIN_R2, ledPwmValue);
}

void LED_LightWhite() {
  int ledPwmValue = 55;
  LED_SetPinPwm(LED_PIN_G1, ledPwmValue); 
  LED_SetPinPwm(LED_PIN_R1, ledPwmValue); 
  LED_SetPinPwm(LED_PIN_B1, ledPwmValue);     
}

void LED_LightWarmWhite() {
  LED_LightWhite(); 
  LED_LightWarm();    
}

// 有连接灯板吗?
void work4() {
    int val = 0;
    Serial.println(val);
    LEDARRAY_Set(val);
}
