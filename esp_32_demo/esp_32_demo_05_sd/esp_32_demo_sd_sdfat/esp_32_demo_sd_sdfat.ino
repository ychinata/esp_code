#include <SPI.h>
#include "SdFat.h"
#include <iostream>
using namespace std;

// author: 小鱼创意
// view: xy, 2023.2.12

SdFs sd;     

void setup() {
    Serial.begin(115200);    
    delay(3000);

    // 初始化
    if(!sd.begin(5)) {      // 使用普通SPI, CS引脚为gpio5
    // if(!sd.begin(SdSpiConfig(5, DEDICATED_SPI, 18000000))) {  // 使用DSPI,会报错,速率18M要如何确定?
        Serial.println("Sd init error");
        return;
    }

    Serial.print("FileSystem Type: ");
    auto fstype = sd.fatType();  
    switch(fstype) {
        case FAT_TYPE_EXFAT:
            Serial.println("ExFat");
            break;
        case FAT_TYPE_FAT32:
            Serial.println("Fat32");
            break;
        case FAT_TYPE_FAT16:
            Serial.println("Fat16");
            break;
        case 0:
            Serial.println("error");
            break;
    }

    auto size = sd.card()->sectorCount() * 512e-9;
    Serial.printf("Size: %f GB \r\n", size);
    
    Serial.println("----------");

    FsFile root;
    FsFile file;   
    if(!root.open("/")) {
        Serial.println("open / error");
        return;
    }

  while (file.openNext(&root, O_RDONLY)) {
    char filename[256];
    if(file.getName(filename, 256) > 0)
      Serial.println(filename);
    file.close();
  }

  Serial.println("--------------");

  if(!file.open("我是中文的.txt", O_RDONLY))
  {
    Serial.println("open error");
    return;
  }
  char buf[256];
  memset(buf, 0, 256);
  file.read(buf, 256);
  Serial.print(buf);
  file.close();
  Serial.println();
  Serial.println("--------------");
  if(!file.open("我是中文的.txt", O_RDWR|O_APPEND))
  {
    Serial.println("open error 1");
  }
  int count = file.write("abcdef");
  Serial.println(count);
  file.close();

}

void loop() {
  // put your main code here, to run repeatedly:
}
