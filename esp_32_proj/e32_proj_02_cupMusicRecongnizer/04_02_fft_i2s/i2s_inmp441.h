 /********************************************************************************************************************************************************
 *                                                                                                                                                       *
 *  Project:         Webspector - WebServer based Spectrum Analyzer                                                                                      *
 *  Target Platform: ESP32                                                                                                                               *
 *                                                                                                                                                       * 
 *  Version: 1.0                                                                                                                                         *
 *  Hardware setup: See github                                                                                                                           *
 *                                                                                                                                                       *
 *                                                                                                                                                       * 
 *  Mark Donners                                                                                                                                         *
 *  The Electronic Engineer                                                                                                                              *
 *  Website:   www.theelectronicengineer.nl                                                                                                              *
 *  facebook:  https://www.facebook.com/TheelectronicEngineer                                                                                            *
 *  youtube:   https://www.youtube.com/channel/UCm5wy-2RoXGjG2F9wpDFF3w                                                                                  *
 *  github:    https://github.com/donnersm                                                                                                               *
 *                                                                                                                                                       *  
 ********************************************************************************************************************************************************/
#ifndef __INMP441_I2S_H__
#define __INMP441_I2S_H__ 	

void I2S_MyInit(void);

#include <driver/i2s.h>

// 为什么放在inmp441.c会报错?
const i2s_port_t I2S_PORT = I2S_NUM_0;


 void I2S_MyInit(void) {	
	 esp_err_t err;
	 
	 Serial.println("Configuring I2S...");	  
	 // The I2S config 
	 const i2s_config_t i2s_config = {
		 .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive mode
		 .sample_rate = FFT_SMP_RATE,						  // 采样率16000, 44100效果不好
		 // could only get it to work with 32bits/24bits 
		 .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, 
		 // leave L/R unconnected when using Left channel
		 .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, 
		 // Philips standard | MSB first standard
		 .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S| I2S_COMM_FORMAT_I2S_MSB),
		 .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,	   // Interrupt level 1
		 .dma_buf_count = 4,						   // number of buffers
		 .dma_buf_len = 8						  // 8 samples per buffer (minimum)
	 };
 
	 // 引脚配置
	 const i2s_pin_config_t pin_config = {
		 .bck_io_num = I2S_SCK,   // BCKL	   //SCK引脚
		 .ws_io_num = I2S_WS,	 // LRCL	 //WS引脚
		 .data_out_num = -1, // not used (only for speakers)
		 .data_in_num = I2S_SD	 // DOUT	 //SD引脚
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



#endif
