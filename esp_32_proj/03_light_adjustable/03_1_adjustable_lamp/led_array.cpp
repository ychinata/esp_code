// 阵列LED的接口：D3/5/6/9
#include "led_array.h"

/*
在一些基于ATmega168和ATmega328的Arduino控制器中，analogWrite()函数支持以下引脚(pwm): 3, 5, 6, 9, 10, 11
http://www.taichi-maker.com/homepage/reference-index/arduino-code-reference/analogwrite/
pwmValue:0到255之间的PWM频率值, 0对应off, 255对应on
*/
void LED_SetPinPwm(int ledPin, int pwmValue) {
    analogWrite(ledPin, pwmValue);
}

void LED_SetPinBlink(int ledPin) {
    digitalWrite(ledPin, HIGH);   // 可选LED_BUILTIN
    delay(500);                       
    digitalWrite(ledPin, LOW);    
    delay(500);                       
}

// 调节灯：AO输出为0-255
void LEDARRAY_Set(int secound_int) {
    // 可优化成查表，减少冗余代码
    if (secound_int > 4700) {
        analogWrite(3, 0);//1
        analogWrite(5, 0);//2
        analogWrite(6, 0);//
        analogWrite(9, 0);
    } else if ((secound_int > 4300) && (secound_int < 4450)) {
        analogWrite(3, 20);//1
        analogWrite(5, 20);//2
        analogWrite(6, 20);//
        analogWrite(9, 20);
//   lcd.setCursor(0, 1);
//    lcd.print(random(0.08,0.15));
    } else if ((secound_int > 4100) && (secound_int < 4250)) {
        analogWrite(3, 50);//1
        analogWrite(5, 50);//2
        analogWrite(6, 50);//
        analogWrite(9, 50);
    } else if ((secound_int > 3900) && (secound_int < 4050)) {
        analogWrite(3, 70);//1
        analogWrite(5, 70);//2
        analogWrite(6, 70);//
        analogWrite(9, 70);
    } else if ((secound_int > 3700) && (secound_int < 3850)) {
        analogWrite(3, 90);//1
        analogWrite(5, 90);//2
        analogWrite(6, 90);//
        analogWrite(9, 90);
    } else if ((secound_int > 3500) && (secound_int < 3650)) {
        analogWrite(3, 105);//1
        analogWrite(5, 105);//2
        analogWrite(6, 105);//
        analogWrite(9, 105);
    } else if ((secound_int > 3300) && (secound_int < 3450)) {
        analogWrite(3, 120);//1
        analogWrite(5, 120);//2
        analogWrite(6, 120);//
        analogWrite(9, 120);
    } else if ((secound_int > 3100) && (secound_int < 3250)) {
        analogWrite(3, 140);//1
        analogWrite(5, 140);//2
        analogWrite(6, 140);//
        analogWrite(9, 140);
    } else if ((secound_int > 1900) && (secound_int < 2050)) {
        analogWrite(3, 160);//1
        analogWrite(5, 160);//2
        analogWrite(6, 160);//
        analogWrite(9, 160);
    } else if ((secound_int > 1700) && (secound_int < 1850)) {
        analogWrite(3, 175);//1
        analogWrite(5, 175);//2
        analogWrite(6, 175);//
        analogWrite(9, 175);
    } else if ((secound_int > 1500) && (secound_int < 1650)) {
        analogWrite(3, 180);//1
        analogWrite(5, 180);//2
        analogWrite(6, 180);//
        analogWrite(9, 180);
    } else if ((secound_int > 1300) && (secound_int < 1450)) {
        analogWrite(3, 205);//1
        analogWrite(5, 205);//2
        analogWrite(6, 205);//
        analogWrite(9, 205);
    } else if ((secound_int > 1100) && (secound_int < 1250)) {
        analogWrite(3, 235);//1
        analogWrite(5, 235);//2
        analogWrite(6, 235);//
        analogWrite(9, 235);
    } else if (secound_int < 1000) {
        analogWrite(3, 255);//1
        analogWrite(5, 255);//2
        analogWrite(6, 255);//
        analogWrite(9, 255);
//    lcd.setCursor(3,1);
//  lcd.print("   ");
//   lcd.setCursor(9, 0);
//  lcd.print("A=0.54");
//  lcd.setCursor(15, 0);
//  lcd.print("a");
//   lcd.setCursor(9, 1);
//  lcd.print("p=4.72");
//  lcd.setCursor(15, 1);
//  lcd.print("w");
    //  // 405开始影响 中心为1700secound_int 2200后中央不受影响
    //  Serial.println(tiaojielight);
    //无外围灯光干扰时的传感器亮度
  }
  
}