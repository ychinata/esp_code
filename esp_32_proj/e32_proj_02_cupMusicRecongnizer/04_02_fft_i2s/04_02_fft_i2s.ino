/**************************
 * 作者：顾加1
 * 日期：2022年1月19日
 * copy后记得一键三连
 */
#include "arduinoFFT.h" // 库管理器安装arduinoFFT库
#include "SSD1306Wire.h"    // 库管理器安装ESP8266 and ESP32 OLED diver for sSD1306 displays库，搜索esp8266-oled-ssd1306
#include "settings.h"
#include "find_music_note.h"
#include "i2s_inmp441.h"


/***************** 全局变量bgn *****************/
SSD1306Wire oled(I2C_ADDR, SDA_PIN, SCL_PIN);
arduinoFFT FFT = arduinoFFT();

// FFT运算相关变量
double vReal[FFT_SMP_NUM];
double vImag[FFT_SMP_NUM];
double vTemp[FFT_SMP_NUM_HALF];
// FFT寻峰数组
int freqNormData[FFT_FINDPEAK_W];
/***************** 全局变量end *****************/


/***************** 函数声明 *****************/
void SmpAndCalcFft(void);
int GetNoteFreqNo(void);



/***************** 函数定义开始 *****************/

// Arduino初始化入口
void setup() {     
    Serial.begin(115200);
	// 屏幕初始化设置
    oled.init();
    oled.flipScreenVertically();        // 设置屏幕翻转
    oled.setContrast(255);              // 设置屏幕亮度
    oled.clear(); 
    oled.display();       // 清除屏幕
    // I2S器件INMP441麦克风初始化
    I2S_MyInit();    
}

// Arduino主循环
void loop() {
	int noteFreqNo = 0;

	noteFreqNo = GetNoteFreqNo();
	Serial.println("获取到的音符频点：");
	Serial.println(noteFreqNo);	// 打印到串口
	
//    delay(100);  //可以适当加延时  
}

// 采样并进行FFT计算音符频点
void SmpAndCalcFft(void) {
	//	Serial.println("start:"+String(micros()));
	static int32_t sample = 0;
	static int bytes_read = 0;
	float mean = 0;

	// 第一步：I2S采样
	for(int i=0;i<FFT_SMP_NUM;i++) {
		bytes_read = i2s_pop_sample(I2S_PORT, (char *)&sample, portMAX_DELAY); // no timeout
		vReal[i] = sample / FFT_TIMEAMP_ATTEN_FACTOR;	//I2S数值太大,压缩一下
		//delay(100);	//如果不延时，串口绘图器基本就是实现更新，效果非常好	
		mean += vReal[i];		 
		vImag[i] = 0.0; 	  
	}
	
	// 第二步：计算均值并归一化
	mean /= FFT_SMP_NUM;	
	for (int i = 0; i < FFT_SMP_NUM; ++i) {
		vReal[i] = vReal[i] / mean;  // 只除不用乘？,先这样处理吧
		//Serial.println("归一化之后的值：");
		if (i < 20) {
			//Serial.println((int)vReal[i]);	
		}		   
	}		 
	//	Serial.println("end:"+String(micros()));	// 计算耗时
		
	//display.clearDisplay();
	//FFT.DCRemoval();
	FFT.Windowing(vReal, FFT_SMP_NUM, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//加窗,可以换不同的窗看效果
	FFT.Compute(vReal, vImag, FFT_SMP_NUM, FFT_FORWARD);  //计算fft
	FFT.ComplexToMagnitude(vReal, vImag, FFT_SMP_NUM);	//计算幅度	  

	// 第三步：存储fft值, OLED画频谱
	//oled.clear();
	//oled.setFont(ArialMT_Plain_10);    
	for (int i = 0; i < FFT_SMP_NUM / 2; i++) {
		int x = map(i, 0, FFT_SMP_NUM / 2, 0, 128);//128是屏幕像素宽度
		int y = map(vReal[i] / FFT_AMP_ATTEN_FACTOR, 0, 4095, 0, 64);	   //64是屏幕像素高度
		oled.drawLine(x, 64, x, 64 - y);
		
		// 重要：存进数组里，用于后续寻找频点
		freqNormData[i] = y;
	}
	//oled.display(); // OLED画频谱
	//delay(500);
}

// 获取音符频点, 返回值为0-511区间,并显示在OLED屏幕上
int GetNoteFreqNo(void) {
	
	SmpAndCalcFft();
	return NOTE_FindMaxNo();
}

