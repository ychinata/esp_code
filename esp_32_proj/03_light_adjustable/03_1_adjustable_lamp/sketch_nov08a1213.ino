/*
#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial myserial(10, 11);
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 16, 2);
// GY-30
// BH1750FVI
// in ADDR 'L' mode 7bit addr
//#define ADDR 0b0100011
// addr 'H' mode
#define ADDR 0b1011100
#define FILTER_A 1
String teststring = "";
//char s;/

String first = "";
String secound = "";
//char d[10];
int first_int = 0;
int secound_int = 0;
//int first_int_begin=0;
//int secound_int_begin=0;
int timess;
int trise = 255;
int lights = 0;
int lights_secound;
int jobss = 1;
int Filter_Value;
int count = 0;
int num = 0;
int i = 0;
float vvv=0;
float aaa;
float ppp;
int Value;
float k = 1.146;
void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  lcd.init(); //初始化LCD
  lcd.backlight();//背光打开// put your setup code here, to run once:
  pinMode(8, INPUT);
  
  //Value=251;
}
void loop() {
//  lights = analogRead(A1);
  //Serial.println(lights);
//  lights_secound = map(lights, 0, 1024, 0, 255);
//  analogWrite(3, 210);//1
//    analogWrite(5, 210);//2
//    analogWrite(6, 210);//
//    analogWrite(9, 210);
//  lcd.setCursor(2, 1);
//  lcd.print(lights_secound);
// if(button(7)){
// Serial.println("1111"); 
// }
// 
  
  // Serial.println(secound_int);
  if (button(8)) {
    jobss++;
    delay(5);
    
  }
  if (jobss == 1) {
    work1();
  }
  if (jobss == 2) {
//    lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("L=");
  lcd.setCursor(3,1);
  lcd.print("    ");
   lcd.setCursor(6,1);
   lcd.print("R");
   lcd.setCursor(0, 0);
  lcd.print("V=8.71");
  lcd.setCursor(6, 0);
  lcd.print("v");
  lcd.setCursor(9, 0);
  lcd.print("A=0.01");
  lcd.setCursor(15, 0);
  lcd.print("a");
   lcd.setCursor(9, 1);
  lcd.print("p=0.01");
  lcd.setCursor(15, 1);
  lcd.print("w");
//    work2();
  }
  if (jobss == 3) {
//    lcd.clear();
//lcd.setCursor(3,1);
//  lcd.print("   ");
    work2();
  }
  if (jobss == 4) {
    jobss = 1;
  }
}
void work1() {
  lights = analogRead(A2);
  //Serial.println(lights);
  lights_secound = map(lights, 0, 1023, 0, 127);
  Serial.println(lights_secound*2); // 串口输出
  analogWrite(3, lights_secound*2);//1
  analogWrite(5, lights_secound*2);//2
  analogWrite(6, lights_secound*2);//
  analogWrite(9, lights_secound*2);
  lcd.setCursor(0, 1);
  lcd.print("L=");
  lcd.setCursor(3,1);
  
  lcd.print(lights_secound*2);
  if ((lights_secound*2<100)&&(lights_secound*2>10)) {
   lcd.setCursor(5,1);
    lcd.print(" ");
//    delay(3);
  }
  if (lights_secound*2<10) {
   lcd.setCursor(4,1);
    lcd.print("  ");
    
//    delay(3);
  }
   lcd.setCursor(6,1);
   lcd.print("R");
   vvv=analogRead(A1);
   float spsps=vvv/100;
   lcd.setCursor(0, 0);
  lcd.print("V=");
  lcd.setCursor(2, 0);
  lcd.print(spsps);
  lcd.setCursor(6, 0);
  lcd.print("v");
  aaa=(analogRead(A0) - 147) * k;//电流大小
// Serial.println(aaa);
  lcd.setCursor(9, 0);
  lcd.print("A=");
  lcd.setCursor(11, 0);
  lcd.print((aaa/1000)-0.019);
  lcd.setCursor(15, 0);
  lcd.print("a");
  
  ppp=((aaa-20)*spsps)/1000;//计算功率
   lcd.setCursor(9, 1);
  lcd.print("p=");
  lcd.print(ppp+0.05);
  lcd.setCursor(15, 1);
  lcd.print("w");
  SOFTSERIAL_Readmsg();
//  Serial.print("xxx");
}
void work2() {
  
 SOFTSERIAL_Readmsg();
 
 Serial.println(secound_int);
  tiaojie();
 
  
}

//此处修改为了 int  void
void  SOFTSERIAL_Readmsg() {
  if (myserial.available() > 0) {
    char s = myserial.read();
    if (s == 'n') {
      // Serial.println(teststring);
      first = teststring;

      teststring = "";
    }
    else if (s == 'v') {
      // Serial.println(teststring);
      secound = teststring;
      teststring = "";
    }
    else {
      teststring += s;
      delay(15);
    }
  }
  first_int = first.toInt();
  secound_int = secound.toInt();
  if (first_int < 0) {
    first_int = first_int * -1;
  }
  if (secound_int < 0) {
    secound_int = secound_int * -1;
  }
  
  //Serial.println(secound_int);
  //此处返回值
  //Serial.println((secound_int*4)+ 100);
//  return ((secound_int * 4) + 100);
//Serial.println(secound_int);
return secound_int;
}



void tiaojie() {
  
  if (secound_int > 4700) {
    analogWrite(3, 0);//1
    analogWrite(5, 0);//2
    analogWrite(6, 0);//
    analogWrite(9, 0);
 
  
  }
  
   
   else if ((secound_int > 4300) && (secound_int < 4450)) {
    analogWrite(3, 20);//1
    analogWrite(5, 20);//2
    analogWrite(6, 20);//
    analogWrite(9, 20);
//   lcd.setCursor(0, 1);
//    lcd.print(random(0.08,0.15));
  }
  else if ((secound_int > 4100) && (secound_int < 4250)) {
   analogWrite(3, 50);//1
    analogWrite(5, 50);//2
    analogWrite(6, 50);//
    analogWrite(9, 50);
  }
   else if ((secound_int > 3900) && (secound_int < 4050)) {
    analogWrite(3, 70);//1
    analogWrite(5, 70);//2
    analogWrite(6, 70);//
    analogWrite(9, 70);
  }
   else if ((secound_int > 3700) && (secound_int < 3850)) {
    analogWrite(3, 90);//1
    analogWrite(5, 90);//2
    analogWrite(6, 90);//
    analogWrite(9, 90);
  }
   else if ((secound_int > 3500) && (secound_int < 3650)) {
  analogWrite(3, 105);//1
    analogWrite(5, 105);//2
    analogWrite(6, 105);//
    analogWrite(9, 105);
  }
  
   else if ((secound_int > 3300) && (secound_int < 3450)) {
    analogWrite(3, 120);//1
    analogWrite(5, 120);//2
    analogWrite(6, 120);//
    analogWrite(9, 120);
  }
  else if ((secound_int > 3100) && (secound_int < 3250)) {
  analogWrite(3, 140);//1
    analogWrite(5, 140);//2
    analogWrite(6, 140);//
    analogWrite(9, 140);
  }
  
   else if ((secound_int > 1900) && (secound_int < 2050)) {
   analogWrite(3, 160);//1
    analogWrite(5, 160);//2
    analogWrite(6, 160);//
    analogWrite(9, 160);
  }
  else if ((secound_int > 1700) && (secound_int < 1850)) {
    analogWrite(3, 175);//1
    analogWrite(5, 175);//2
    analogWrite(6, 175);//
    analogWrite(9, 175);
  }
  else if ((secound_int > 1500) && (secound_int < 1650)) {
   analogWrite(3, 180);//1
    analogWrite(5, 180);//2
    analogWrite(6, 180);//
    analogWrite(9, 180);
    
  }
  else if ((secound_int > 1300) && (secound_int < 1450)) {
    analogWrite(3, 205);//1
    analogWrite(5, 205);//2
    analogWrite(6, 205);//
    analogWrite(9, 205);
  }
  else if ((secound_int > 1100) && (secound_int < 1250)) {
    analogWrite(3, 235);//1
    analogWrite(5, 235);//2
    analogWrite(6, 235);//
    analogWrite(9, 235);
  }
  else if (secound_int < 1000) {
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

bool button(int pin)
{
  if (digitalRead(pin))
  {
    delay(20);
    //    if(digitalRead(pin))
    while (digitalRead(pin));
    return 1;
  }
  return 0;
}

*/