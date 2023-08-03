#include <Arduino.h>
#include "SSD1306Wire.h"
#include <arduinoFFT.h>

/* 引脚

//OLED
P21
P22<-->SCL
//DAC->喇叭
P25
//ADC接麦克风
P32
*/

// 宏定义
#define BUTTON_PIN 2
#define DAC_PIN 25
#define ADC_PIN 32
#define NUM_SAMPLES 128
/* 设置oled屏幕的相关信息 */
#define SDA_PIN 21                       // SDA引脚，默认gpio4
#define SCL_PIN 22                       // SCL引脚，默认gpio5

/***************** 全局变量bgn *****************/
/* 新建一个oled屏幕对象，需要输入IIC地址，SDA和SCL引脚号 */
const int I2C_ADDR = 0x3c;              // oled屏幕的I2c地址
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);

// FFT
const double samplingFrequency = 20000; //Hz, 声音采样频率
unsigned int sampling_period_us;
arduinoFFT FFT = arduinoFFT();


uint16_t lFre[]{262, 294, 330, 349, 392, 440, 494};         //C调低音1-7的频率
uint16_t mFre[]{523, 587, 659, 698, 784, 880, 988};         //C调中音1-7的频率
uint16_t hFre[]{1047, 1175, 1319, 1397, 1568, 1760, 1967};  //C调高音1-7的频率

int i = 0;
int pos = 0;
int AdcValue = 32;

hw_timer_t * mytimer;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

//计算正弦所要的
double w = 0;
double a = 50;
uint8_t c = 127;
uint64_t count = 0;

// MIDI音乐
uint16_t baseDuration = 1000;     //一拍1S
struct Midi
{
  uint8_t Scale;     //音阶 1-7 中音， 11- 17 低音 21-27高音
  uint8_t Duration;  //节拍数 1:1拍  2：1/2   4: 1/4   5:3/4
};

//两只老虎数组
Midi tiger[]{
  {1, 2}, {2, 2}, {3, 2}, {1, 2},   {1, 2}, {2, 2}, {3, 2}, {1, 2},
  {3, 2}, {4, 2}, {5, 2}, {0, 2},   {3, 2}, {4, 2}, {5, 2}, {0, 2},
  {5, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {1, 2},    {5, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {1, 2},
  {1, 2}, {15, 2}, {1, 5}, {0, 4},     {1, 2}, {15, 2}, {1, 5}, {0, 4},
  {0, 1}, {0, 1}
};
/***************** 全局变量end *****************/

void IRAM_ATTR timer_isr()
{
    portENTER_CRITICAL_ISR(&mux);
    if(w == 0) {
        dacWrite(DAC_PIN, 0);
    } else {
        double t = count++ * 100e-6;
        uint8_t val = a*sin(w*t)+c;
        dacWrite(DAC_PIN, val);
    }
    portEXIT_CRITICAL_ISR(&mux);
}

//播放一个音符，使用dac输出
void PlayMusicScaleDac(const Midi& mid)
{
  uint32_t fre = 0;
  uint32_t duration = 1000;
  if(mid.Duration == 2)
    duration = 500;
  else if(mid.Duration == 4)
    duration = 250;
  else if(mid.Duration == 5)
    duration = 750;

  if(mid.Scale == 0)
    fre = 0;
  else if(mid.Scale < 10)  //是中音
    fre = mFre[mid.Scale-1];
  else if(mid.Scale < 20) //是低音
    fre = lFre[mid.Scale - 11];
  else if(mid.Scale < 30)
    fre = hFre[mid.Scale - 21];

  portENTER_CRITICAL(&mux);
  if(fre == 0)
    w = 0;
  else
    w = fre * 2*3.14159265;
  count = 0;
  portEXIT_CRITICAL(&mux);
  
  delay(duration);
}

void setup() {
    Serial.begin(115200);
    oled.init();
    oled.flipScreenVertically();        // 设置屏幕翻转
    oled.setContrast(255);              // 设置屏幕亮度
    oled.clear(); 
    oled.display();       // 清除屏幕
    pinMode(BUTTON_PIN,INPUT);   
    analogReadResolution(12);                            //精度12位 0 --- 4095
    analogSetPinAttenuation(ADC_PIN, ADC_11db);          //150 mV ~ 2450 mV

    sampling_period_us = round(1000000*(1.0/samplingFrequency)); //计算采样频率
    Serial.printf("采样频率 = Hz %f\n", samplingFrequency);
    Serial.printf("采样周期 = us %d\n", sampling_period_us);
  
    mytimer = timerBegin(0, 80, true);
    timerAttachInterrupt(mytimer, timer_isr, true);
    //100us触发一次
    timerAlarmWrite(mytimer, 100, true);
    
    //开启定时器
    timerAlarmEnable(mytimer);

}

bool musicOn = false;
void loop()
{
  int totalValue = 0;
  if (digitalRead(BUTTON_PIN) == HIGH) 
  {
    // 按键被按下
    musicOn = !musicOn; // 切换音乐开关状态
    delay(20); // 延迟一段时间以避免按键抖动
    if (musicOn) 
    {
      for(i=0;i<14;i++)
      { 
        if (pos >= sizeof(tiger) / sizeof(Midi))
        pos = 0;
        PlayMusicScaleDac(tiger[pos++]);
      } 
      PlayMusicScaleDac(tiger[0,0]);
    }
  }
  
    double vReal[NUM_SAMPLES];
    double vImag[NUM_SAMPLES];
    
    for (int i = 0; i < NUM_SAMPLES; i++) {
        vReal[i] = analogRead(ADC_PIN);  //获取指定GPIO口ADC的值 uint16_t analogRead(uint8_t pin);
        vImag[i] = 0;
        //50us -> 20kHz
        //250us -> 4kHz
        delayMicroseconds(sampling_period_us);            //获取指定GPIO口电压值 (毫伏值) uint32_t analogReadMilliVolts(uint8 t pin);        
    }
    
    FFT.Windowing(vReal, NUM_SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    //FFT.Windowing(vReal, 1, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, NUM_SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, NUM_SAMPLES);
    
    oled.clear();
    oled.setFont(ArialMT_Plain_10);
    
    for (int i = 0; i < NUM_SAMPLES / 2; i++) {
        int x = map(i, 0, NUM_SAMPLES / 2, 0, 128);//128是屏幕像素宽度
        int y = map(vReal[i], 0, 4095, 0, 64);      //64是屏幕像素高度
        oled.drawLine(x, 64, x, 64 - y);
    }
    
    oled.display();
    
    delay(100);
}
