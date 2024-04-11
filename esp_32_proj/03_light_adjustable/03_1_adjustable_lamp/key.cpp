#include "key.h"

static int g_keyMoterState = LOW;   // 不加static编译会提示重复定义

int KEY_Init(void) {
    pinMode(KEY1_PIN, INPUT_PULLUP);  // 输入模式
    pinMode(KEY2_PIN, INPUT_PULLUP);  // 输入模式
    pinMode(KEY3_PIN, INPUT_PULLUP);  // 输入模式
    pinMode(KEY4_PIN, INPUT_PULLUP);  // 输入模式    
}

//20240330
// 按键检测
int KEY_IsPressDown(void)
{
    int isKeyPressDown = 0;
    if (digitalRead(KEY1_PIN) == LOW) {       // 按键按下
        delay(20);                          // 延时消抖
        while (digitalRead(KEY1_PIN) == LOW); // 等待松手
        //delay(20);                          // 延时消抖
        isKeyPressDown = 1;
    }
    if (digitalRead(KEY2_PIN) == LOW) {       // 按键按下
        delay(20);                          // 延时消抖
        while (digitalRead(KEY2_PIN) == LOW); // 等待松手
        isKeyPressDown = 1;
    }    
    return isKeyPressDown;
}

//20240411
// 按键检测-很难检测到key2
int KEY_GetValue2(void)
{
    int keyValue = 0;
    if (digitalRead(KEY1_PIN) == LOW) {       // 按键按下
        delay(20);                          // 延时消抖
        while (digitalRead(KEY1_PIN) == LOW); // 等待松手
        //delay(20);                          // 延时消抖
        keyValue = 1;
    }
    if (digitalRead(KEY2_PIN) == LOW) {       // 按键按下
        delay(20);                          // 延时消抖
        while (digitalRead(KEY2_PIN) == LOW); // 等待松手
        keyValue = 2;
    }    
    return keyValue;
}

//20240411
// 按键检测-很难检测到key2
int KEY_GetValue(void)
{
    int keyValue = 0;
    int keyState = 0;
    if (digitalRead(KEY2_PIN) == LOW) {
        keyValue = 1;
    } else if (digitalRead(KEY1_PIN) == LOW) {
        keyValue = 2;
    }

    if (keyValue == 1 || keyValue == 2) {       // 按键按下
        delay(20);                          // 延时消抖
        while ((digitalRead(KEY2_PIN) == LOW) || (digitalRead(KEY1_PIN) == LOW)); // 等待松手
        //delay(20);                          // 延时消抖
        return keyValue;
    }  
    return 0;
}