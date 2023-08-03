/**************************
 * 作者：顾加1
 * 日期：2022年1月19日
 * copy后记得一键三连
 */
#include "arduinoFFT.h"
#include "SSD1306Wire.h"

#define samples 512 //采样点数，2的N次幂
#define NUM_SAMPLES 512

#define halfsamples samples/2
#define NumofCopy halfsamples*sizeof(double)
#define Interval 128/(halfsamples)
//Adafruit_SSD1306 display(100);
arduinoFFT FFT = arduinoFFT();

double vReal[samples];
double vImag[samples];
double vTemp[halfsamples];

/* 设置oled屏幕的相关信息 */
#define SDA_PIN 21                       // SDA引脚，默认gpio4
#define SCL_PIN 22                       // SCL引脚，默认gpio5

#define BUTTON_PIN 2
#define DAC_PIN 25
#define ADC_PIN 32

/***************** 全局变量bgn *****************/
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */
const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);

void setup() {     
    Serial.begin(115200);
    oled.init();
    oled.flipScreenVertically();        // 设置屏幕翻转
    oled.setContrast(255);              // 设置屏幕亮度
    oled.clear(); 
    oled.display();       // 清除屏幕
    pinMode(BUTTON_PIN,INPUT);   
    //analogReadResolution(12);                            //精度12位 0 --- 4095
    //analogSetPinAttenuation(ADC_PIN, ADC_11db);          //150 mV ~ 2450 mV

    //setP32();  //设置32分频,加快AD采样
}

void loop() {
//  Serial.println("start:"+String(micros()));
    for(int i=0;i<samples;i++)
    {
        vReal[i]=analogRead(ADC_PIN)-512;  //采样
        vImag[i] = 0.0;
    }
//  Serial.println("end:"+String(micros()));
    //display.clearDisplay();
    FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//加窗
    FFT.Compute(vReal, vImag, samples, FFT_FORWARD);  //计算fft
    FFT.ComplexToMagnitude(vReal, vImag, samples);  //计算幅度
    
//    for(int i=0;i<halfsamples;i++)
//    {
//        display.drawPixel(i*Interval,vTemp[halfsamples-i-1]*0.007+1, WHITE); //显示
//        display.drawLine(i*Interval, 0, i*Interval,vReal[halfsamples-i-1]*0.007, WHITE);
//    }
//    display.display();
//    memcpy(vTemp, vReal, NumofCopy);
//    delay(20);  //改为128点时可以注释掉，防止刷新太慢

    // 画频谱
    oled.clear();
    oled.setFont(ArialMT_Plain_10);    
    for (int i = 0; i < NUM_SAMPLES / 2; i++) {
        int x = map(i, 0, NUM_SAMPLES / 2, 0, 128);//128是屏幕像素宽度
        int y = map(vReal[i] / 8, 0, 4095, 0, 64);      //64是屏幕像素高度
        oled.drawLine(x, 64, x, 64 - y);
    }    
    oled.display();    
    delay(100);
}

//void setP32()//设置32分频
//{
//      ADCSRA|=(1<<ADPS2);  
//      ADCSRA&=~(1<<ADPS1);
//      ADCSRA|=(1<<ADPS0);
//}
//
//void setP16( ) {  //设置16分频，不建议
//      ADCSRA |=  (1 << ADPS2);   // 1
//      ADCSRA &=  ~(1 << ADPS1);  // 0
//      ADCSRA &=  ~(1 << ADPS0);  // 0
//}
