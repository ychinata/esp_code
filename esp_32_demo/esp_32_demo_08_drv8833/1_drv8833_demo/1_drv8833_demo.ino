#include <analogWrite.h>    // 安装库ESP32 AnalogWrite
#include "car.h"
/*
Date:2024.1.10
*/

void setup() {
    // put your setup code here, to run once:    
    Serial.begin(115200);
    Car_Init();
}

void loop() {
    // put your main code here, to run repeatedly:
    //CAR_Test2();
    int speed = 255;
    //CAR_ForwardAll(speed);  // 前进ok
}

void CAR_Test2(void) {
    int speed = 255;    //     
    CAR4_Clkwise(speed);
    delay(2000);
}

// success
void CAR_Test1(void) {
    int speed = 255;    // 
 
    CAR_ForwardAll(speed);  // 前进ok
    delay(2000); 
    CAR4_ForwardLeft(speed);    // 前左转ok
    delay(2000); 

    CAR4_StopF();//准备后转
    CAR4_BackwardLeft(speed);   // 后左转
    delay(2000);    
    CAR4_StopF();

    CAR4_StopB();//准备前转
    CAR4_ForwardRight(speed);   // 前右转ok
    delay(2000); 

    CAR4_StopF();//准备后转
    CAR4_BackwardRight(speed);  // 后右转
    delay(2000);    
    CAR_BackwardAll(speed); // 单独后退ok
    delay(2000);
    CAR4_StopB();//准备前转
}

//LF-RF-LB-RB
void CAR_ForwardAll(unsigned int speed) {
    DRV8833_LF_Forward(speed);
    DRV8833_RF_Forward(speed);
    DRV8833_LB_Forward(speed);
    DRV8833_RB_Forward(speed);
}
 
void CAR_BackwardAll(unsigned int speed) {
    DRV8833_LF_Backward(speed);
    DRV8833_RF_Backward(speed);    
    DRV8833_LB_Backward(speed);
    DRV8833_RB_Backward(speed);
}



///////////////////////////////DRV8833控制电机

void MOTOR_SetSpeed(int pin, unsigned int speed)
{
    if (speed > 255) {
        speed = 255;    // analogwrite限制
    }
    analogWrite(pin, speed);
}

// FORWARD
void DRV8833_LF_Forward(unsigned int speed)
{
    // LF
    //digitalWrite(BIN1,1);
    MOTOR_SetSpeed(BIN1, speed);    
    digitalWrite(BIN2,0);    
}

void DRV8833_RF_Forward(unsigned int speed)
{
    // RF
    digitalWrite(AIN1,0);    
    //digitalWrite(AIN2,1);
    MOTOR_SetSpeed(AIN2, speed);
}

void DRV8833_LB_Forward(unsigned int speed)
{
    // LB
    digitalWrite(BACK_AIN1, 0);    
    //digitalWrite(BACK_AIN2,1); 
    MOTOR_SetSpeed(BACK_AIN2, speed); 
}

void DRV8833_RB_Forward(unsigned int speed)
{
    // RB
    //digitalWrite(BACK_BIN1,1);
    MOTOR_SetSpeed(BACK_BIN1, speed);
    digitalWrite(BACK_BIN2,0);    
}

// BACKWARD
void DRV8833_LF_Backward(unsigned int speed)
{
    // LF
    digitalWrite(BIN1,0);
    //digitalWrite(BIN2,1);
    MOTOR_SetSpeed(BIN2, speed);
}

void DRV8833_RF_Backward(unsigned int speed)
{
    // RF
    //digitalWrite(AIN1,1);
    MOTOR_SetSpeed(AIN1, speed);
    digitalWrite(AIN2,0);  
}

void DRV8833_LB_Backward(unsigned int speed)
{
    // LB
    //digitalWrite(BACK_AIN1,1);
    MOTOR_SetSpeed(BACK_AIN1, speed);
    digitalWrite(BACK_AIN2,0); 
}

void DRV8833_RB_Backward(unsigned int speed)
{
    // RB
    digitalWrite(BACK_BIN1,0);
    //digitalWrite(BACK_BIN2,1);
    MOTOR_SetSpeed(BACK_BIN2, speed);
}