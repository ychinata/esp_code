/********************************************
 *@File: 基于ESP32的LED调光灯 
 *@Author: xxy
 *@Date: 2024.3.27
 *********************************************/
#include <Wire.h>
//#include <BasicEncoder.h>   //库BasicEncoder
#include "bh1750.h"
#include "key.h"
#include "led_array.h"
//#include "oled_i2c_adafruit.h"
//#include "power_measure.h"
#include "rotary_encoder.h"

void setup() {
    // 模块初始化begin
    Serial.begin(9600);
    BH1750_Init();                  //初始化BH1750
    //OLED_I2C_Adafruit_Init();  
    ROTARYENCODER_Init();  
    // 一路灯板D4
    pinMode(LED_PIN_COLD, OUTPUT);
    pinMode(LED_PIN_WARM, OUTPUT);
    LED_Init();
    // key
    KEY_Init();
    // 模块初始化end

    // 初始配置
    //LED_TurnOnRgbAll();
    //LED_TurnOnRgbOnBorad();
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
    //LED_TurnOn(255);
    //LED_LightWhite();
    //delay(1000); 
    //LED_TurnOff();
    //LED_TurnOn();
    //LED_SetAllKindofColorOnBorad();
    LEDAPP_ChangeClorModeofRbgOnBoradWithKey();
    
    ROTARYENCODER_Show();       // 调光值维测
    //Serial.println(ledPwmValue);
    lux = BH1750_GetData();               // 获取光照强度数据

    //show
    //OLED_ShowBright(brightValue, ledPwmValue, lux);
    ROTARYENCODER_Show();
}

// 有连接灯板吗?
void work4() {
    int val = 0;
    Serial.println(val);
    LEDARRAY_Set(val);
}
