#ifndef __CAR_H__
#define __CAR_H__

#include "Arduino.h"

#define PWMA 6
#define AIN2 7
#define AIN1 8

#define PWMB 11
#define BIN2 10
#define BIN1 9


void motordir(unsigned char out1, unsigned char out2, unsigned char out3, unsigned char out4);
void motor_Speed(unsigned int PWM1,unsigned int PWM2);

/*******************  本次使用  **********************/
void motor(int L1,int R1);

void Car_Init();
void Up(unsigned int pwm);
void Back(unsigned int pwm);
void niShiZhen(unsigned int pwm);   //原地逆时针旋转
void shunShiZhen(unsigned int pwm); //原地顺时针旋转
void topLeft(unsigned int pwm);
void topRight(unsigned int pwm);
void bottomLeft(unsigned int pwm);
void bottomRight(unsigned int pwm);
void Stop();

void Upup();  //直线行驶一段距离
void Left90(); //左转90度
void Right90(); //右转90度
void Turn_round(); //掉头
/****************************************************/





#endif
