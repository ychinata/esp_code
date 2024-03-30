#include "key.h"

//20240330
// 按键检测
int KEY_IsPressDown(void)
{
    int isKeyPressDown = LOW;
    if (digitalRead(KEY_PIN) == LOW) {       // 按键按下
        delay(20);                          // 延时消抖
        while (digitalRead(KEY_PIN) == LOW); // 等待松手
        delay(20);                          // 延时消抖
        isKeyPressDown = 1;
    }
    return isKeyPressDown;
}