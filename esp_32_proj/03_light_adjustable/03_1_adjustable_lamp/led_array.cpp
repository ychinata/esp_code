// 阵列LED的接口：D3/5/6/9
#include "led_array.h"
#include "key.h"

static int g_ledRgbOnBoardState = 0;   // 不加static编译会提示重复定义

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
    
    // 一路灯板D4
    pinMode(LED_PIN, OUTPUT);
    
    //pinMode(LED_PIN_COLD, OUTPUT);
    //pinMode(LED_PIN_WARM, OUTPUT);
    //LED_RGB5050Init();           
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

//2024.4.11
void LED_SetLedRgbOnBoardState(int state)
{
    g_ledRgbOnBoardState = state;
}

//2024.4.11
int LED_GetLedRgbOnBoardState(void)
{
    return g_ledRgbOnBoardState;
}

//2024.4.11
void LED_ChangeLedRgbOnBoardState(int mode)
{
    if (1 == mode) {
        g_ledRgbOnBoardState++;
        if (g_ledRgbOnBoardState >= 8) {
            g_ledRgbOnBoardState = 0;
        }        
    } else if (2 == mode) {
        g_ledRgbOnBoardState--;    
        if (g_ledRgbOnBoardState < 0) {
            g_ledRgbOnBoardState = 7;
        }               
    } else {

    }
}

/* 应用层 */
//2024.4.11
// KEY_GetValue只能调用一次，不能多次调用。这个错误重复犯了！2024.4.12
void LEDAPP_ChangeClorModeofRbgOnBoradWithKey(void) {
    int keyValue = 0;
    keyValue = KEY_GetValue();
    if (1 == keyValue) {
        LED_ChangeLedRgbOnBoardState(1);
    } else if (2 == keyValue) {
        LED_ChangeLedRgbOnBoardState(2);
    } else {

    }
    LED_SetColorOnBorad(g_ledRgbOnBoardState);
}
