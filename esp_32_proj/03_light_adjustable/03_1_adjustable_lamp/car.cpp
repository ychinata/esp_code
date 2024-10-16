#include "car.h"

void Car_Init()
{
   /*初始化小车控制IO*/
    pinMode(PWMA,OUTPUT);
    pinMode(AIN2,OUTPUT);
    pinMode(AIN1,OUTPUT);
    pinMode(PWMB,OUTPUT);
    pinMode(BIN2,OUTPUT);
    pinMode(BIN1,OUTPUT);

    CAR_Stop(); /*初始停止转动*/
}


/***********  小车状态函数  ************/
void motordir(unsigned char out1, unsigned char out2, unsigned char out3, unsigned char out4)   //输入1 0，控制方向
{
    digitalWrite(AIN2,out1);
    digitalWrite(AIN1,out2);
    digitalWrite(BIN1,out3);
    digitalWrite(BIN2,out4);
}

void motor_Speed(unsigned int PWM1,unsigned int PWM2)
{
    analogWrite(PWMA,PWM1);   //左电机
    analogWrite(PWMB,PWM2); //右电机
}

void motor(int L1,int R1) /*电机转向、速度处理*/ 
{
    if (abs(L1) > 255) L1 = L1 / abs(L1) * 255;   
    if (abs(R1) > 255) R1 = R1 / abs(R1) * 255;
//  if (abs(L1) == 0) L1 = 1; //abs() 绝对值计算
//  if (abs(R1) == 0) R1 = 1;
  
    if (L1 > 0 && R1 > 0) {
        motor_Speed(L1,R1);
        motordir(0, 1, 0, 1);  //正转
    } else if (- L1 > 0 && - R1 > 0) {
        motor_Speed(-L1,-R1);
        motordir(1, 0, 1, 0);   //反转
    } else if (- L1 > 0 && R1 > 0) {
        motor_Speed(-L1,R1);
        motordir(1, 0, 0, 1); 
    } else if (L1 > 0 && -R1 > 0) {
        motor_Speed(L1,-R1);
        motordir(0,1, 1,0);
    } else if (L1 ==0 && R1 ==0) {
        CAR_Stop();
    } else  CAR_Stop();
  
}
/********************************/


void CAR_Up(unsigned int pwm){  //前进
    motordir(0,1,0,1);
    motor_Speed(pwm,pwm);
}

void CAR_Back(unsigned int pwm){  //后退
    motordir(1,0,1,0);
    motor_Speed(pwm,pwm);
}

void CAR_topLeft(unsigned int pwm){    //前进左转
    motordir(0,1,0,1);
    pwm=pwm+10; if(pwm>=255)pwm=255;
    motor_Speed(pwm*1/5,pwm);
}

void CAR_topRight(unsigned int pwm){   //前进右转
    motordir(0,1,0,1);
    pwm=pwm+10; if(pwm>=255)pwm=255;
    motor_Speed(pwm,pwm*1/5);
}

void CAR_bottomLeft(unsigned int pwm){    //后退左转
    motordir(1,0,1,0);
    pwm=pwm+10; if(pwm>=255)pwm=255;
    motor_Speed(pwm*1/5,pwm);
}

void CAR_bottomRight(unsigned int pwm){   //后退右转
    motordir(1,0,1,0);
    pwm=pwm+10; if(pwm>=255)pwm=255;
    motor_Speed( pwm,pwm*1/5 );
}

void CAR_niShiZhen(unsigned int pwm){    //原地逆时针旋转
    motordir(1,0,0,1);
    motor_Speed( pwm,pwm );
}
 
void CAR_shunShiZhen(unsigned int pwm){   //原地顺时针旋转
    motordir(0,1,1,0);
    motor_Speed( pwm,pwm );
}
  
void CAR_Stop(){    //停车
    digitalWrite(AIN2,LOW);
    digitalWrite(AIN1,LOW);
    digitalWrite(BIN1,LOW);
    digitalWrite(BIN2,LOW);
    /*下面这句可以不写*/  
    motor_Speed(0,0);
}


//=======================================

void CAR_Upup(){
    CAR_Up(150);
    delay(250); 
}

void CAR_Left90(){ //左转90度
    CAR_Upup();
    CAR_shunShiZhen(200); //原地顺时针旋转
    delay(515);
}
void CAR_Right90(){ //右转90度
    CAR_Upup();
    CAR_niShiZhen(200);   //原地逆时针旋转
    delay(500);     
}
void CAR_Turn_round(){ //掉头
    CAR_shunShiZhen(200); //原地顺时针旋转
    delay(1040);
}
