// 阵列LED的接口：D3/5/6/9
#include "led_array.h"

//2024.4.11
void LED_RGB5050Init(void) {
    //RGB5050LED1
    pinMode(LED_PIN_G1, OUTPUT);
    pinMode(LED_PIN_R1, OUTPUT);
    pinMode(LED_PIN_B1, OUTPUT);
    //RGB5050LED2    
    pinMode(LED_PIN_R2, OUTPUT);
    pinMode(LED_PIN_G2, OUTPUT);
    pinMode(LED_PIN_B2, OUTPUT);      
    //RGB5050LED3
    pinMode(LED_PIN_R3, OUTPUT);
    pinMode(LED_PIN_G3, OUTPUT);
    pinMode(LED_PIN_B3, OUTPUT);
}

//2024.4.11
void LED_Init(void) {
    LED_RGB5050Init();           
}

/*
在一些基于ATmega168和ATmega328的Arduino控制器中，analogWrite()函数支持以下引脚(pwm): 3, 5, 6, 9, 10, 11
http://www.taichi-maker.com/homepage/reference-index/arduino-code-reference/analogwrite/
pwmValue:0到255之间的PWM频率值, 0对应off, 255对应on
*/
void LED_SetPinPwm(int ledPin, int pwmValue) {
    analogWrite(ledPin, pwmValue);
}

//2024.3.30
// 输出设置为0, 关闭所有灯, LED负极接IO
void LED_TurnOff(void) {
    digitalWrite(LED_PIN_COLD, HIGH);   //输出3V3，正极接5V，灯灭
    digitalWrite(LED_PIN_WARM, HIGH);
    //digitalWrite(LED_PIN_WARM, LOW);    //输出2.2V，为什么不是0V
}

//2024.3.27
void LED_TurnOnWarm(int ledPwmValue) {
    LED_SetPinPwm(LED_PIN_R1, ledPwmValue);
}

//2024.3.27
void LED_TurnOnCold(int ledPwmValue) {
    LED_SetPinPwm(LED_PIN_G1, ledPwmValue);    
}

//2024.3.27
void LED_TurnOnLevel(int ledPwmValue) {
    LED_TurnOnWarm(ledPwmValue); 
    LED_TurnOnCold(ledPwmValue);    
}

//2024.3.30
void LED_TurnOn(void) {
    digitalWrite(LED_PIN_WARM, LOW);
    digitalWrite(LED_PIN_COLD, LOW);
}

void LED_SetPinBlink(int ledPin) {
    digitalWrite(ledPin, HIGH);   // 可选LED_BUILTIN
    delay(500);                       
    digitalWrite(ledPin, LOW);    
    delay(500);                       
}

//2024.4.11
void LED_SetRgbAll(int state) {
    digitalWrite(LED_PIN_R1, state);
    digitalWrite(LED_PIN_G1, state);
    digitalWrite(LED_PIN_B1, state);
    digitalWrite(LED_PIN_R2, state);
    digitalWrite(LED_PIN_G2, state);
    digitalWrite(LED_PIN_B2, state);    
}

//2024.4.11
void LED_TurnOnRgbAll(void) {
    LED_SetRgbAll(HIGH);
}

//2024.4.11
void LED_TurnOffRgbAll(void) {
    LED_SetRgbAll(LOW);
}

//2024.4.11
void LED_SetRgbOnBorad(int state) {
    digitalWrite(LED_PIN_R3, state);
    digitalWrite(LED_PIN_G3, state);
    digitalWrite(LED_PIN_B3, state); 
}

//2024.4.11
void LED_TurnOnRgbOnBorad(void) {
    LED_SetRgbAll(LOW);
}

//2024.4.11
void LED_TurnOffRgbOnBorad(void) {
    LED_SetRgbAll(HIGH);
}

//2024.4.11
// 8种颜色组合，代码可优化
void LED_SetColorOnBorad(int colorState) {
    int turnOn = LOW;
    int turnOff = HIGH;
    switch (colorState) {
    case 0/* 绿色 */:
        digitalWrite(LED_PIN_R3, turnOff);
        digitalWrite(LED_PIN_B3, turnOff);
        digitalWrite(LED_PIN_G3, turnOn); 
        break;          
    case 1/* 蓝色 */:
        digitalWrite(LED_PIN_R3, turnOff);
        digitalWrite(LED_PIN_B3, turnOn);
        digitalWrite(LED_PIN_G3, turnOff); 
        break;
    case 2/* 青色 */:
        digitalWrite(LED_PIN_R3, turnOff);
        digitalWrite(LED_PIN_B3, turnOn);
        digitalWrite(LED_PIN_G3, turnOn); 
        break;
    case 3/* 红色 */:
        digitalWrite(LED_PIN_R3, turnOn);
        digitalWrite(LED_PIN_B3, turnOff);
        digitalWrite(LED_PIN_G3, turnOff); 
        break;   
    case 4/* 黄色 */:
        digitalWrite(LED_PIN_R3, turnOn);
        digitalWrite(LED_PIN_B3, turnOff);
        digitalWrite(LED_PIN_G3, turnOn); 
        break;     
    case 5/* 粉色 */:
        digitalWrite(LED_PIN_R3, turnOn);
        digitalWrite(LED_PIN_B3, turnOn);
        digitalWrite(LED_PIN_G3, turnOff); 
        break;  
    case 6/* 白色 */:
        digitalWrite(LED_PIN_R3, turnOn);
        digitalWrite(LED_PIN_B3, turnOn);
        digitalWrite(LED_PIN_G3, turnOn); 
        break;     
    case 7/* 灭 */:
        digitalWrite(LED_PIN_R3, turnOff);
        digitalWrite(LED_PIN_B3, turnOff);
        digitalWrite(LED_PIN_G3, turnOff); 
        break;                                     
    default:
        break;
    }
}

//2024.4.11
// RGB灯遍历不同颜色
void LED_SetAllKindofColorOnBorad(void) {
    for (int i = 0; i < 8; i++) {
        LED_SetColorOnBorad(i);
        delay(1000);
    }
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
