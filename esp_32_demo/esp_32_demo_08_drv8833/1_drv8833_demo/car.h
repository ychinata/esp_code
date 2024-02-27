#ifndef __CAR_H__
#define __CAR_H__

#include "Arduino.h"

/* 驭风小车V3
1.U1-AIN25/33,BIN26/27
U2-AIN16/4,BIN17/18
*/

// foreward wheel
#define PWMA 25
#define AIN1 25
#define AIN2 33

#define PWMB 26
#define BIN1 26
#define BIN2 27

//backward wheel
#define BACK_PWMA 16
#define BACK_AIN1 16
#define BACK_AIN2 4

#define BACK_PWMB 17
#define BACK_BIN1 17
#define BACK_BIN2 18


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