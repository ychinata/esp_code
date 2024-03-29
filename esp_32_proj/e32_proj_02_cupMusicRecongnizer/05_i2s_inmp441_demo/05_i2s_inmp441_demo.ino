/** 
 * ESP32 I2S Serial Plotter Example.
 * 在串口绘图器中显示声音波形
 */
#include <driver/i2s.h>
const i2s_port_t I2S_PORT = I2S_NUM_0; 

/* INM441引脚 */
// 03配置-波形不对！
//#define I2S_WS 5
//#define I2S_SD 27
//#define I2S_SCK 26
// 05博客原始配置
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2

void setup() {
    Serial.begin(115200);
    Serial.println("Configuring I2S...");
    esp_err_t err;
    
    // The I2S config 
    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX), // Receive mode
        .sample_rate = 16000,                         // 采样率
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

void loop() {

    // Read a single sample and log it for the Serial Plotter.
    int32_t sample = 0;
    int bytes_read = i2s_pop_sample(I2S_PORT, (char *)&sample, portMAX_DELAY); // no timeout
    if (bytes_read > 0) {
        Serial.println(sample);
    } 
    //delay(100);   //如果不延时，串口绘图器基本就是实现更新，效果非常好
}
