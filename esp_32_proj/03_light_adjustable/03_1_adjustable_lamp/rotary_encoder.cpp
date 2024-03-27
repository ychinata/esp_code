/********************************************
 *@File: 旋转编码器读取（不带开关），使用中断实现
 *@Author: xxy
 *@Date: 2024.2.13
    参考：https://blog.csdn.net/lihe4151021/article/details/121776815
     顺时针转一圈：80
    逆时针转一圈：-80
 *********************************************/
#include "rotary_encoder.h"

//volatile long temp, encoderCounter =0; //This variable will increase or decreas depending on the rotation of encoder
int counterLast = 0;
int encoderCounter = 0; //This variable will increase or decreas depending on the rotation of encoder
int encoderPinA = 2; //interrupt pin 2 
int encoderPinB = 3; //interrrupt pin 3

// 初始化
void ROTARYENCODER_Init(void) {
    // encoder setup
    pinMode(encoderPinA, INPUT); 
    pinMode(encoderPinB, INPUT); 
    //Setting up interrupt
    //attach an interrupt to pin encoderPinA & encoderPinA of the Arduino, and when the pulse is in the CHANGE edge 
    //  called the function
    //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 isDigitalPin nr 3 on moust Arduino.
    attachInterrupt(digitalPinToInterrupt(encoderPinA), ROTARYENCODER_INTA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinB), ROTARYENCODER_INTB, CHANGE);
}

// 获取编码器数据/角度
double ROTARYENCODER_GetData(void) {
    double angle = 0.0;
    // Send the value of counter
    //double angle = encoderCounter*360/172032.0;//ppr=172032
    return angle = encoderCounter*4.5;  //一圈对应数值80
}

// 维测函数
void ROTARYENCODER_Show(void) {
    double angle = 0.0;
    angle = ROTARYENCODER_GetData();
    // 编码器值有变化，才打印，避免刷屏
    if (encoderCounter!= counterLast) {        
        counterLast = encoderCounter;  // 更新
        //Serial.println(encoderCounter);
        Serial.print(angle);
        Serial.println("°");
    }
}

// 中断响应函数-A相
void ROTARYENCODER_INTA() {
    // look for a low-to-high on channel A
    if (digitalRead(encoderPinA) == HIGH) { 
        // check channel B to see which way encoder is turning
        if (digitalRead(encoderPinB) == LOW) {  
            encoderCounter = encoderCounter + 1;         // CW
        } else {
            encoderCounter = encoderCounter - 1;         // CCW
        }
    } else {   // must be a high-to-low edge on channel A                                       
        // check channel B to see which way encoder is turning  
        if (digitalRead(encoderPinB) == HIGH) {   
            encoderCounter = encoderCounter + 1;          // CW
        } else {
            encoderCounter = encoderCounter - 1;          // CCW
        }
    }
    // Serial.println(encoder0Pos, DEC);          
    // use for debugging - remember to comment out
}

// 中断响应函数-B相
void ROTARYENCODER_INTB() {
    // look for a low-to-high on channel B
    if (digitalRead(encoderPinB) == HIGH) {   
        // check channel A to see which way encoder is turning
        if (digitalRead(encoderPinA) == HIGH) {  
            encoderCounter = encoderCounter + 1;         // CW
        } else {
            encoderCounter = encoderCounter - 1;         // CCW
        }
    } else { // Look for a high-to-low on channel B
        // check channel B to see which way encoder is turning  
        if (digitalRead(encoderPinA) == LOW) {   
            encoderCounter = encoderCounter + 1;          // CW
        } else {
            encoderCounter = encoderCounter - 1;          // CCW
        }
    }
}