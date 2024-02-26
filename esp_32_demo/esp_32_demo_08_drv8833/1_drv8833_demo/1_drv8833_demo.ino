
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
    digitalWrite(AIN2,0);
    digitalWrite(AIN1,1);
    digitalWrite(BIN1,1);
    digitalWrite(BIN2,0); 
    delay(100); 
}
