/********************************************
 *@File: 基于ESP32的LED调光灯 
 *@Author: xxy
 *@Date: 2024.3.27
 *********************************************/
#include <Wire.h>
//#include <BasicEncoder.h>   //库BasicEncoder
#include "bh1750.h"
#include "car.h"
#include "dht11.h"
#include "key.h"
#include "led_array.h"
#include "oled_i2c_adafruit.h"
//#include "power_measure.h"
#include "rotary_encoder.h"

int motorState = 0;

void setup() {
    // 模块初始化begin
    Serial.begin(9600);
    BH1750_Init();                  //初始化BH1750
    OLED_I2C_Adafruit_Init();  
    ROTARYENCODER_Init();  

    LED_Init();
    // key
    KEY_Init();
    DHT11_Init();
    Car_Init();
    // 模块初始化end

    // 初始配置
    //LED_TurnOnRgbAll();
    //LED_TurnOnRgbOnBorad();
}

// 2024.10.16
void loop() {
    //Serial.println(lights);
    double brightValue = 0.0;
    int ledPwmValue = 0;
    int lux = 0;
    float humidity = 0.0;
    float temp = 0.0; 
    int carPwmValue = 0;
    int keyNum = 0;
    
    keyNum = KEY_GetValue();                        // 响应不灵敏，考虑用外部中断
    if (keyNum == 3) {
        motorState++;
    }
    //brightValue = 100;
    brightValue = ROTARYENCODER_GetData();          // 获取编码器设定的亮度值
    ledPwmValue = map(brightValue, 0, 360, 0, 255); // 将编码器原始值0-360映射到pwm值0-255,超出0-360的范围会重新映射
    LED_SetPinPwm(LED_PIN, ledPwmValue);            // 调光
    ROTARYENCODER_Show();                           // 调光值维测
    //Serial.println(ledPwmValue);
    lux = BH1750_GetData();                         // 获取光照强度数据
    Serial.println(lux);
    DHT11_Getdata(&humidity, &temp);                // 获取温度和温度    
    //DHT11_Showdata();   
    // 电机控制 
    if (motorState%2 == 1) {    
        if (ledPwmValue > 255) {
            carPwmValue = 255;
        } else if (ledPwmValue < 0) {
            carPwmValue = 0;
        } else {
            carPwmValue = ledPwmValue;
        }
        CAR_Up(carPwmValue);                            // 电机转动
    } else {
        CAR_Up(0);                            // 电机转动
    }
    OLED_ShowBright(brightValue, carPwmValue, motorState, humidity, temp);
    delay(1000);                                    // 延时1s也可以捕获编码器，但数码值不准确
}

// 2024.4.12
void loop_old() {
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


