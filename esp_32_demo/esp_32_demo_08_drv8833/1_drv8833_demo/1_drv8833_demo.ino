
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
    CAR_ForwardM12(0);
    CAR_ForwardM34(0);
    delay(100); 
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
