#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "fs_io.h"

/*
* 硬件连接：如下
*
* SD Card -- ESP32:

* CS  -- GPIO5
* CLK -- GPIO18
* MISO-- GPIO19
* MOSI-- GPIO23
* GND -- GND
* VCC --3.3V/VIN
* 
*/

//http://www.esp32learning.com/code/esp32-and-microsd-card-example.php
// View: xy, 2023.2.12

void setup(){
    Serial.begin(115200);
    Serial.println("----SD Card Test------");
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    
    uint8_t cardType = SD.cardType();    
    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }
     
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }
     
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
     
    listDir(SD, "/", 0);
    createDir(SD, "/mydir");
    
    listDir(SD, "/", 0);
    removeDir(SD, "/mydir");
    
    listDir(SD, "/", 2);
    writeFile(SD, "/hello.txt", "Hello ");
    appendFile(SD, "/hello.txt", "World!\n");
    readFile(SD, "/hello.txt");
    deleteFile(SD, "/foo.txt");
    renameFile(SD, "/hello.txt", "/foo.txt");
    readFile(SD, "/foo.txt");
    testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

/* 程序主循环 */
void loop(){
 
}

