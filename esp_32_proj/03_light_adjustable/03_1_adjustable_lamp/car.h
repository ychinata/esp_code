#ifndef __CAR_H__
#define __CAR_H__

#include "Arduino.h"
#include <analogWrite.h>

#define PWMA 35
#define AIN2 33
#define AIN1 25

#define PWMB 13
#define BIN2 12
#define BIN1 14


void motordir(unsigned char out1, unsigned char out2, unsigned char out3, unsigned char out4);
void motor_Speed(unsigned int PWM1,unsigned int PWM2);

/*******************  本次使用  **********************/
void motor(int L1,int R1);

void Car_Init();
void CAR_Up(unsigned int pwm);
void CAR_Back(unsigned int pwm);
void CAR_niShiZhen(unsigned int pwm);   //原地逆时针旋转
void CAR_shunShiZhen(unsigned int pwm); //原地顺时针旋转
void CAR_topLeft(unsigned int pwm);
void CAR_topRight(unsigned int pwm);
void CAR_bottomLeft(unsigned int pwm);
void CAR_bottomRight(unsigned int pwm);
void CAR_Stop();

void CAR_Upup();  //直线行驶一段距离
void CAR_Left90(); //左转90度
void CAR_Right90(); //右转90度
void CAR_Turn_round(); //掉头
/****************************************************/





#endif
