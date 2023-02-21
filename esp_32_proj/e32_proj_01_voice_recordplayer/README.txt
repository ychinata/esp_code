//TODO
1.麦克风换成I2S设备，降低噪声
2.功放换成I2S设备，降低噪声
3.麦克风+功放换成I2S设备
4.更换喇叭
5.使用噪音滤波算法
6.ESP32之间使用I2S无线传输音频
7.联网上传音频
8.音频智能信号分析处理

//硬件增加
按键、OLED
参考：https://www.bilibili.com/video/BV19e4y1574Y

//Bug

1.现象
17:08:22.931 -> E (2634) I2S: /home/runner/work/esp32-arduino-lib-builder/esp32-arduino-lib-builder/esp-idf/components/driver/i2s.c:1214 (i2s_write):tx NULL
17:08:22.931 -> recvSize: 2048
原因：record函数最后没加mi.End

2.现象：磁盘有写保护
解决方法：SD读卡器上有一个写保护开关，被打开了！

3.SD初始化失败
现象：2023.3.26 热拔插几遍SD卡，突然就一直初始化失败。折腾了两个钟后，又拔了一次SD卡模块，突然就好了！可能是面包板接触不良，快画PCB板！
