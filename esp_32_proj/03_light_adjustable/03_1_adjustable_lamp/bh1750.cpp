/****************************************bh1750 part****************************************/
/*
  接线：
  3.3------VCC
  GND------GND
  SCL------SCL
  SDA------SDA
    https://blog.csdn.net/qq_55490300/article/details/130967259  
*/
//#include <Arduino.h>
//#include <math.h>                                                   //调用库文件  
#include <Wire.h>                                                   //调用库文件 
#include "bh1750.h"

int bh1750_address = 0x23;                                           //设备IIC地址
byte buff[2];                                                       //定义数组
unsigned long g_bh1750Times = 0;                                      //记录设备运行时间

/* BH1750初始化地址 */
void BH1750_Init(void) {
    Wire.begin();                                                     //IIC通讯初始化
    Wire.beginTransmission(bh1750_address);
    Wire.write(0x10);
    Wire.endTransmission();
}

/* BH1750读取数据 */
int BH1750_Read(int address) {
    int i = 0;
    int ret;

    Wire.beginTransmission(address);
    Wire.requestFrom(address, 2);   // 读取两字节
    while (Wire.available()) {
        buff[i] = Wire.read();                                          //接收一个字节
        i++;
    }
    Wire.endTransmission();
    if (i == 2) {   // 检验是否读取到两字节
        ret = BH1750_OK;
    } else {
        ret = BH1750_ERR;
    }
    return ret;
}

/* BH1750获取数据 */
int BH1750_GetData(void) {
    int lux;
    if (BH1750_OK == BH1750_Read(bh1750_address)) {
        lux = ((buff[0] << 8) | buff[1]) / 1.2;
    }
    return lux;
}

/* BH1750获取数据 */
void BH1750_ShowData(void) {
    int lux;
    if (millis() - g_bh1750Times >= bh1750TimeInterval) {              //一定时间执行一次
        g_bh1750Times = millis();
        lux = BH1750_GetData();
        Serial.print(lux);                                     //串口打印对应的值
        Serial.println("[lx]");                                      //串口打印对应的值
    }
}