/**************************
 * 作者：顾加1
 * 日期：2022年1月19日
 * copy后记得一键三连
 */
#include "arduinoFFT.h" // 库管理器安装arduinoFFT库
#include "SSD1306Wire.h"    // 库管理器安装ESP8266 and ESP32 OLED diver for sSD1306 displays库，搜索esp8266-oled-ssd1306
#include "settings.h"
#include "find_music_note.h"
#include <driver/i2s.h>
const i2s_port_t I2S_PORT = I2S_NUM_0;

// FFT配置
#define samples 1024 //采样点数，2的N次幂.可以换成64/128/256/512/1024等看效果，必须是2^n
#define NUM_SAMPLES 1024 // 要和samples保持一致
#define halfsamples samples/2
#define NumofCopy halfsamples*sizeof(double)
#define Interval 128/(halfsamples)
#define FFT_AMP_ATTEN_FACTOR 10     // 幅值衰减因子.ADC时为100效果可以
#define FFT_TIMEAMP_ATTEN_FACTOR 1000     // 幅值衰减因子.ADC时为100效果可以


// 
#define FFT_SMP_RATE 10000

arduinoFFT FFT = arduinoFFT();

double vReal[samples];
double vImag[samples];
double vTemp[halfsamples];

int freqNormData[OLED_PIXEL_W];  // OLED_PIXEL_W+1

// 引脚配置
// 05博客原始配置
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2



#define BUTTON_PIN 2
#define DAC_PIN 25                      // 接麦克风
#define ADC_PIN 32                      // 接扬声器

/***************** 全局变量bgn *****************/
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);


void I2S_MyInit(void) {    
    esp_err_t err;
    
    Serial.println("Configuring I2S...");    
    // The I2S config 
    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive mode
        .sample_rate = FFT_SMP_RATE,                         // 采样率16000, 44100效果不好
        // could only get it to work with 32bits/24bits 
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, 
        // leave L/R unconnected when using Left channel
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, 
        // Philips standard | MSB first standard
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S| I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,     // Interrupt level 1
        .dma_buf_count = 4,                           // number of buffers
        .dma_buf_len = 8                         // 8 samples per buffer (minimum)
    };

    // 引脚配置
    const i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_SCK,   // BCKL      //SCK引脚
        .ws_io_num = I2S_WS,    // LRCL     //WS引脚
        .data_out_num = -1, // not used (only for speakers)
        .data_in_num = I2S_SD   // DOUT     //SD引脚
                                        //L/R引脚接地
    };

    // Configuring the I2S driver and pins.
    // This function must be called before any I2S driver read/write operations.
    err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        Serial.printf("Failed installing driver: %d\n", err);
        while (true);
    }
    err = i2s_set_pin(I2S_PORT, &pin_config);
    if (err != ESP_OK) {
        Serial.printf("Failed setting pin: %d\n", err);
        while (true);
    }
    Serial.println("I2S driver installed.");        
}

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

    I2S_MyInit();    
}

void loop() {
//  Serial.println("start:"+String(micros()));
    static int32_t sample = 0;
    static int bytes_read = 0;
    float mean = 0;
    
    for(int i=0;i<samples;i++) {
        // ADC采样
        //vReal[i] = analogRead(ADC_PIN)-512;  //采样
        //vReal[i] = analogRead(ADC_PIN);  //采样,不减掉一个直流也可以  

        // I2S采样
        bytes_read = i2s_pop_sample(I2S_PORT, (char *)&sample, portMAX_DELAY); // no timeout
//        if (bytes_read > 0) {
//            Serial.println(sample);
//        }
        vReal[i] = sample / FFT_TIMEAMP_ATTEN_FACTOR;
        //vReal[i] = sample;
        //delay(100);   //如果不延时，串口绘图器基本就是实现更新，效果非常好   
        mean += vReal[i];
        
        vImag[i] = 0.0;
        if (i < 20) {
            //Serial.println(vReal[i]);    
        }        
    }
    // 计算均值
    mean /= samples;    
    //Serial.printf("均值为：%f", mean);
//    Serial.println("均值为：");
//    Serial.println(mean);
    for (int i = 0; i < samples; ++i) {
        vReal[i] = vReal[i] / mean;  // 只除不用乘？
        //Serial.println("归一化之后的值：");
        if (i < 20) {
            //Serial.println((int)vReal[i]);    
        }          
    }
    
    
//  Serial.println("end:"+String(micros()));    
        
    //display.clearDisplay();
    //FFT.DCRemoval();
    FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//加窗,可以换不同的窗看效果
    FFT.Compute(vReal, vImag, samples, FFT_FORWARD);  //计算fft
    FFT.ComplexToMagnitude(vReal, vImag, samples);  //计算幅度    

    // 画频谱
    int maxtmpY = 0;
    int maxtmpX = 0;
    oled.clear();
    oled.setFont(ArialMT_Plain_10);    
    for (int i = 0; i < NUM_SAMPLES / 2; i++) {
        int x = map(i, 0, NUM_SAMPLES / 2, 0, 128);//128是屏幕像素宽度
        int y = map(vReal[i] / FFT_AMP_ATTEN_FACTOR, 0, 4095, 0, 64);      //64是屏幕像素高度
        oled.drawLine(x, 64, x, 64 - y);
        //
        freqNormData[x] = y;
    }    
    oled.display();
    delay(500);

    NOTE_Show();
    delay(500);


//    delay(20);  //改为128点时可以注释掉，防止刷新太慢    
}
