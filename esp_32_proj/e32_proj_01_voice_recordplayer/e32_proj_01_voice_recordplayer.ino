#include <SPI.h>
#include "SdFat.h"
#include "MyI2S.h"
#include "wave.h"
// 内置SD
#include "FS.h"
#include "SD.h"
#include "fs_io.h"
// 内置SD

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

#define SCK  	18
#define MISO  	19
#define MOSI  	23
#define CS  	5

/***************** 内部函数声明 ******************/
void WAV_Record();
void WAV_Play();

/***************** 全局变量声明 ******************/
MyI2S mi;	// g_I2s
const char filename[] = "/my_record_adc_2s.wav";
const int record_time = 2;  // second, 记录音频的时长
const int waveDataSize = record_time * 88200;

/***************** record ******************/
//数据流:recvI2SBuffer->writeFileBuff
char writeFileBuff[1024];		// sendI2SBuffer
int16_t recvI2SBuffer[1024];  //接收I2S缓冲区
/***************** record ******************/

/***************** play ******************/
//数据流:readFileBuff->sendI2SBuffer
int16_t readFileBuff[1024];        //接收缓冲区, =u8*2048,readFileBuff
int16_t sendI2SBuffer[2048];   //发往I2S的缓冲区
/***************** play ******************/

// 主函数启动
void setup() {
	Serial.begin(115200);
	delay(500);

	// 初始化SD卡
    //pinMode(CS, OUTPUT);	// 可不加
	/*
	// 初始化方式1
	if(!SD.begin()) {				
		Serial.println("init sd card error");
		return;
	}
	*/
	// 初始化方式2
	SPIClass spi = SPIClass(VSPI);
	spi.begin(SCK, MISO, MOSI, CS);
	if (!SD.begin(CS, spi, 10000000)) {
		Serial.println("init sd card error");
		return;
	}	

	// 录音并生成wav文件, 保存在SD卡中
	WAV_Record();

	// 读取SD卡中的wav文件，并播放
	WAV_Play();
}


// 主循环
void loop() {
	// put your main code here, to run repeatedly:

}


/*********************
 * Func:   播放wav文件, 从SD卡中读取
 * Author: xy
 * Date:   2023.2.21
 *********************/ 
void WAV_Play() {	// (filename)
	//打印文件	
    listDir(SD, "/", 0);	

	//打开文件
    File file = SD.open(filename);	
	
	if(!file) {
		Serial.println("open file error");
		return;
	}

	//跳过WAV头部直接到数据部分
	file.seek(sizeof(WAV_HEADER));

	if(!mi.InitDacOutput(I2S_BITS_PER_SAMPLE_16BIT)) {
		Serial.println("init i2s error");
		return;
	}

	Serial.println("Play start!");

	int recvSize = 0;
	do {
		recvSize =  file.read((uint8_t*)readFileBuff, 2048);	// u16*1024->u8*2048
    	// Serial.printf("recvSize: %d\n", recvSize);
	
		for(int i = 0; i<recvSize/2; i++) {		//相当于u16*2048
			sendI2SBuffer[2*i] = readFileBuff[i];       //左声道,左右声道数据填充一致
			sendI2SBuffer[2*i+1] = readFileBuff[i];     //右声道
		}

		mi.Write((char*)sendI2SBuffer, recvSize*2);
	} while(recvSize>0);
	file.close();
	mi.End();		// 不加会有错误
	Serial.println("Play finish!");
}

/*********************
 * Func:   录音并生成wav文件, 存储到SD卡中
 * Author: xy
 * Date:   2023.3.25
 *********************/ 
void WAV_Record() {
	//打印文件	
    listDir(SD, "/", 0);

	// 已存在文件则不重新录制
	if (FSIO_SD_IsExistFile(SD, filename)) {
		return;
	}

	//删除并创建文件
    deleteFile(SD, filename);

	//写模式创建新文件	
	File file = SD.open(filename, FILE_WRITE);	
	if(!file) {
		Serial.println("create file error");
		return;
	}

	//填充wav文件头, 16bit单声道
	auto header = CreateWaveHeader(1, 44100, 16);
	header.riffSize = waveDataSize + 44 - 8;
	header.dataSize = waveDataSize;
	file.write((const uint8_t*)&header, 44);	// sd/sdfat一致

	// I2S-ADC初始化
	if(!mi.InitAdcInput(I2S_BITS_PER_SAMPLE_16BIT, ADC1_CHANNEL_7)) {
		Serial.println("init i2s error");
		return;
	}
	Serial.println("Record start!");

	// 
	for (int j = 0; j < waveDataSize/1024; ++j) {
		auto sz = mi.Read((char*)recvI2SBuffer, 2048);	//获取IS2接口中ADC输入数据
		char*p =(char*)(recvI2SBuffer);		// 16bit*1024转8bit*2048\
		//写入1个1024 byte的数据块
		for(int i=0;i<sz/2;i++) {
			recvI2SBuffer[i] = recvI2SBuffer[i] & 0x0FFF;	// ADC是12bit,只有低12bit有效
			recvI2SBuffer[i] *= 7;		// 声音存储前放大7倍
			if(i%2 == 0) {					// 每2次填充2个u8(1个u16),即抛弃掉其中一个声道?
				writeFileBuff[i] = p[2*i];
				writeFileBuff[i + 1] = p[2*i + 1];
			}
		}
		file.write((const byte*)writeFileBuff, 1024);	// sd/sdfat一致
	}
	file.close();	// sd/sdfat一致
	mi.End();		// 不加会有错误
	Serial.println("Record finish!");
}


