/********************************************
 *@File: DTH11
        需要安装两个库：DHT sensor library和Adafruit Unified Sensor
 *@Author: Cseexy
 *@Date: 2024.10.6
 *@Description:             
 *********************************************/
#include <DHT.h>  // 安装DHT sensor library和Adafruit Unified Sensor两个库
#include"dht11.h"

//定义针脚
#define DHTPIN 15
//定义类型，DHT11或者其它
#define DHTTYPE DHT11
//进行初始设置 
DHT dht(DHTPIN, DHTTYPE);

void DHT11_Init() {
    dht.begin();                    //DHT开始工作
}

/* 获取DHT11的温度和湿度
 * 结果为两位小数：Humidity: 52.00, Temperature: 30.40
 */
void DHT11_Getdata(float* humidity, float* temp) {
    if (humidity == nullptr || temp == nullptr) {
        Serial.print("DHT11_Getdata error! Nullptr.");
        return;
    }
    // 两次检测之间，要等几秒钟，这个传感器有点慢。
    //delay(2000);
    // 读温度或湿度要用250毫秒
    *humidity = dht.readHumidity();//读湿度
    *temp = dht.readTemperature();//读温度，默认为摄氏度
}

void DHT11_Showdata() {
    float humidity = 0.0;
    float temp = 0.0;

    DHT11_Getdata(&humidity, &temp);
    Serial.print("Humidity: ");//湿度
    Serial.println(humidity);
    Serial.print("Temperature: ");//温度
    Serial.print(temp);
    Serial.println(" ℃ ");
}