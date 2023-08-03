#include <TimeLib.h>
#include "arduinoFFT.h"
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

//https://gitee.com/adamhxx/arduino-open-source/blob/master/Arduino-Audio-Visualizer/ESP32C3-FFT-8x32/ESP32C3-FFT-8x32.ino
/********************FFT相关定义**********************************/
#define CHANNEL 5  //选择音频输入IO口序号为4
// 32*8的像素显示
#define xres 32            // Total number of  columns in the display
#define yres 8            // Total number of  rows in the display

arduinoFFT FFT = arduinoFFT(); //创建FFT对象

//FFT参数
const uint16_t SAMPLES = 64; //采样点数，必须为2的整数次幂
const double samplingFrequency = 4000; //Hz, 声音采样频率

unsigned int sampling_period_us;
unsigned long microseconds;
unsigned long lastTime = 0;

double vReal[SAMPLES]; //FFT采样输入样本数组
double vImag[SAMPLES]; //FFT运算输出数组
int freq_gain2[xres] = {30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
int Intensity[xres] = {}; // initialize Frequency Intensity to zero
int Displacement = 1;          // Create LED Object

//FFT参数，保持默认即可
#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03
/********************FFT相关定义*********************************/


/*******************灯板参数定义*********************************/
#define LED_PIN     2  //灯板输入IO口选择
#define BRIGHTNESS  10  //默认背光亮度
#define LED_TYPE    WS2812  //灯珠类型
#define COLOR_ORDER GRB  //色彩顺序

/*******************灯板参数定义*********************************/
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(xres, yres, 1, 1, LED_PIN,
                            NEO_MATRIX_TOP  + NEO_TILE_LEFT  + NEO_MATRIX_COLUMNS   + NEO_MATRIX_PROGRESSIVE +
                            NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_GRB + NEO_KHZ800);

//RGB颜色数组https://www.sojson.com/rgb.html
const int16_t rgbArray[32] = {
  matrix.Color(255,0,0),
  matrix.Color(255,191,0),
  
  matrix.Color(127,255,0),
  matrix.Color(0,255,36),
  
  matrix.Color(0,255,255),
  matrix.Color(0,63,255),
  
  matrix.Color(255,0,191),
  matrix.Color(238,106,167)
};

void setup(){
    Serial.begin(115200);
    sampling_period_us = round(1000000*(1.0/samplingFrequency)); //计算采样频率
    pinMode(CHANNEL,INPUT); //初始化麦克风接口为输入模式，表示读取麦克风数据
    matrix.setBrightness(100);  

    Serial.printf("采样频率 = Hz %d\n", samplingFrequency);
    Serial.printf("采样周期 = us %d\n", sampling_period_us);
    //Serial.printf("This chip has %d cores\n", ESP.getChipCores());    
}

void loop() {
  //Collect Samples
    getSamples();
    //Update Display
    displayUpdate();
    matrix.show();
    delay(1);
}

// 采样
void getSamples(){
    // 计算采样耗时？
    microseconds = micros();
    for(int i = 0; i < SAMPLES; i++){
        vReal[i] = analogRead(CHANNEL);
        Serial.println(vReal[i]);
        //Serial.println(String(i)+": "+String(vReal[i]));
        vImag[i] = 0;
        //while(micros() - microseconds < sampling_period_us){
        //empty loop
        // }
        microseconds += sampling_period_us;
    }
    bool reduce = false;
    if ((millis() - lastTime) > 25) {
        lastTime = millis();
        reduce = true;
    }
    // micros()和millis()是什么？
    
    //FFT计算
    FFT.Windowing(vReal, 1, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    
    //Update Intensity Array  
    int t = 16;
    for(int i = t; i < (xres*Displacement)+t; i+=Displacement){
        vReal[i] = constrain(vReal[i], 0 ,3596);            // 限制FFT值幅的最大值
        vReal[i] = map(vReal[i], freq_gain2[(i-t)/Displacement], 1848, 0, yres);        // map data to fit our display
        if(reduce){
            Intensity[(i-t)/Displacement] --;                      // Decrease displayed value
        }
        if (vReal[i] > Intensity[(i-t)/Displacement])          // Match displayed value to measured value
            Intensity[(i-t)/Displacement] = vReal[i];
    }
}

void displayUpdate(){
  int color = 0;
  for(int i = 0; i < xres; i++){
    drawFastYLine(i,yres-Intensity[i],Intensity[i],hsv2rgb(color, 80, 80 ));
    drawFastYLine(i,0,yres-1-Intensity[i],matrix.Color(0,0,0));
    color += 360/xres;
  } 
}

void drawFastYLine(int16_t x, int16_t y, int16_t h, int16_t c){
  for(int i=y;i<y+h;i++){
    matrix.drawPixel(x,i,c);
  }
}

uint16_t hsv2rgb(uint16_t hue, uint8_t saturation, uint8_t value)
{
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint16_t hi = (hue / 60) % 6;
    uint16_t F = 100 * hue / 60 - 100 * hi;
    uint16_t P = value * (100 - saturation) / 100;
    uint16_t Q = value * (10000 - F * saturation) / 10000;
    uint16_t T = value * (10000 - saturation * (100 - F)) / 10000;

    switch (hi)
    {
    case 0:
        red = value;
        green = T;
        blue = P;
        break;
    case 1:
        red = Q;
        green = value;
        blue = P;
        break;
    case 2:
        red = P;
        green = value;
        blue = T;
        break;
    case 3:
        red = P;
        green = Q;
        blue = value;
        break;
    case 4:
        red = T;
        green = P;
        blue = value;
        break;
    case 5:
        red = value;
        green = P;
        blue = Q;
        break;
    default:
        return matrix.Color(255, 0, 0);
    }
    red = red * 255 / 100;
    green = green * 255 / 100;
    blue = blue * 255 / 100;
    return matrix.Color(red, green, blue);
}
