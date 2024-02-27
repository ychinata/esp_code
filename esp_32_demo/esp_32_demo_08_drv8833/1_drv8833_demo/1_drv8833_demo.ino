
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
    CAR_ForwardAll();
    delay(2000); 
    CAR_BackwardAll();
    delay(2000);
}

void CAR_ForwardM12(unsigned int pwm){  //前进
    //motordir(0,1,0,1);
    // RF
    digitalWrite(AIN1,0);    
    digitalWrite(AIN2,1);
    // LF
    digitalWrite(BIN1,1);
    digitalWrite(BIN2,0);    
    //motor_Speed(pwm,pwm);
}

void CAR_ForwardM34(unsigned int pwm){  //前进
    //motordir(0,1,0,1);
    // LB
    digitalWrite(BACK_AIN1,0);    
    digitalWrite(BACK_AIN2,1);
    // RB
    digitalWrite(BACK_BIN1,1);
    digitalWrite(BACK_BIN2,0);    
    //motor_Speed(pwm,pwm);
}


//LF-RF-LB-RB
void CAR_ForwardAll(void) {
    DRV8833_LF_Forward();
    DRV8833_RF_Forward();
    DRV8833_LB_Forward();
    DRV8833_RB_Forward();
}
 
void CAR_BackwardAll(void) {
    DRV8833_LF_Backward();
    DRV8833_RF_Backward();    
    DRV8833_LB_Backward();
    DRV8833_RB_Backward();
}

// FORWARD
void DRV8833_LF_Forward(void)
{
    // LF
    digitalWrite(BIN1,1);
    digitalWrite(BIN2,0);    
}

void DRV8833_RF_Forward(void)
{
    // RF
    digitalWrite(AIN1,0);    
    digitalWrite(AIN2,1);  
}

void DRV8833_LB_Forward(void)
{
    // LB
    digitalWrite(BACK_AIN1,0);    
    digitalWrite(BACK_AIN2,1); 
}

void DRV8833_RB_Forward(void)
{
    // RB
    digitalWrite(BACK_BIN1,1);
    digitalWrite(BACK_BIN2,0);    
}

// BACKWARD
void DRV8833_LF_Backward(void)
{
    // LF
    digitalWrite(BIN1,0);
    digitalWrite(BIN2,1);    
}

void DRV8833_RF_Backward(void)
{
    // RF
    digitalWrite(AIN1,1);    
    digitalWrite(AIN2,0);  
}

void DRV8833_LB_Backward(void)
{
    // LB
    digitalWrite(BACK_AIN1,1);    
    digitalWrite(BACK_AIN2,0); 
}

void DRV8833_RB_Backward(void)
{
    // RB
    digitalWrite(BACK_BIN1,0);
    digitalWrite(BACK_BIN2,1);    
}