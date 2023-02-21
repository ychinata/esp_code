#include <SPI.h>
#include "SdFat.h"
#include "MyI2S.h"
#include "wave.h"
// 内置SD
#include "FS.h"
#include "SD.h"
#include "fs_io.h"
// 内置SD

//SdFs sd;      // sd卡
//FsFile file;  // 录音文件

/*
* 硬件连接：如下
* --------------
* SD Card -- ESP32:
* CS  -- GPIO5
* CLK -- GPIO18
* MISO-- GPIO19
* MOSI-- GPIO23
* GND -- GND
* VCC --3.3V/VIN
* --------------
* MAX4466 -- ESP32:
* OUT -- GPIO35
* --------------
* LM386功放 -- ESP32:
* IN -- GPIO25/26
*/


MyI2S mi;
const int record_time = 2;  // second
//const char filename[] = "/我的录音Adc.wav";
const char filename[] = "/my_record_adc_2s.wav";

const int waveDataSize = record_time * 88200;
int16_t communicationData[1024];  //接收缓冲区
char partWavData[1024];

void setup() {
	Serial.begin(115200);
	delay(500);

	// 初始化SD卡
	if(!SD.begin()) {		
		Serial.println("init sd card error");
		return;
	}

	//打印文件	
    listDir(SD, "/", 0);

	//删除并创建文件
    deleteFile(SD, filename);

	//写模式创建新文件	
	File file = SD.open(filename, FILE_WRITE);	
	if(!file) {
		Serial.println("crate file error");
		return;
	}

	//填充wav文件头
	auto header = CreateWaveHeader(1, 44100, 16);
	header.riffSize = waveDataSize + 44 - 8;
	header.dataSize = waveDataSize;
	file.write((const uint8_t*)&header, 44);	// sd/sdfat一致

	// I2S-ADC初始化
	if(!mi.InitAdcInput(I2S_BITS_PER_SAMPLE_16BIT, ADC1_CHANNEL_7)) {
		Serial.println("init i2s error");
		return;
	}
	Serial.println("start");

	// 
	for (int j = 0; j < waveDataSize/1024; ++j) {
		auto sz = mi.Read((char*)communicationData, 2048);	//获取IS2接口中ADC输入数据
		char*p =(char*)(communicationData);		// 16bit*1024转8bit*2048\
		//循环1024
		for(int i=0;i<sz/2;i++) {
			communicationData[i] = communicationData[i] & 0x0FFF;	// ADC是12bit,只有低12bit有效
			communicationData[i] *= 7;		// 声音存储前放大
			if(i%2 == 0) {					// 每2次填充2个u8(1个u16),即抛弃掉其中一个声道?
				partWavData[i] = p[2*i];
				partWavData[i + 1] = p[2*i + 1];
			}
		}
		file.write((const byte*)partWavData, 1024);	// sd/sdfat一致
	}
	file.close();	// sd/sdfat一致
	Serial.println("finish");
}

void loop() {
	// put your main code here, to run repeatedly:

}

