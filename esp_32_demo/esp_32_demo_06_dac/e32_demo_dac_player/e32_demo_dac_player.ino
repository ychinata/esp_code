#include <SPI.h>
//#include "SdFat.h"
#include "MyI2S.h"
#include "wave.h"
// 内置SD
#include "FS.h"
#include "SD.h"
#include "fs_io.h"
// 内置SD


//SdFs sd;      // sd卡
//FsFile file;  // 录音文件

MyI2S mi;
//const char filename[] = "/我的录音.wav";
const char filename[] = "/my_record_adc.wav";

int16_t buffer[1024];        //接收缓冲区, =u8*2048
int16_t partWavData[2048];   //发往I2S的缓冲区

void setup() {
	Serial.begin(115200);
	delay(500);

	// 初始化SD卡
	//if(!sd.begin(SdSpiConfig(5, DEDICATED_SPI, 18000000))) {
	if(!SD.begin()) {				
		Serial.println("init sd card error");
		return;
	}

	//打开文件
	//file = sd.open(filename, O_READ);
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

	Serial.println("start: read wav file");

	int recvSize = 0;
	do {
		recvSize =  file.read((uint8_t*)buffer, 2048);	// u16*1024->u8*2048,代码需要调整
    	Serial.printf("recvSize: %d\n", recvSize);
	
		for(int i = 0; i<recvSize/2; i++) {		//相当于u16*2048
			buffer[i] += 0x8000;				//adc数据调整
			partWavData[2*i] = buffer[i];       //左声道,左右声道数据填充一致
			partWavData[2*i+1] = buffer[i];     //右声道
		}

		mi.Write((char*)partWavData, recvSize*2);	//改成*4?还是不用改?
	} while(recvSize>0);
	file.close();
	mi.End();
	Serial.println("finish: read wav file");
}

void loop() {
  // put your main code here, to run repeatedly:

}

