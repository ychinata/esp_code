#include "FS.h"
#include "SD.h"
#include "fs_io.h"

// File Created by xy
// 2023.2.12

// 列出目录
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("[Listing directory]: %s\n", dirname);
    
    File root = fs.open(dirname);
    // 打开目录失败
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    // 目录名不是目录
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }
    // 遍历目录里的文件
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){     // 若是目录
            Serial.print(" DIR : ");
            Serial.println(file.name());
            // 嵌套遍历子目录
            if (levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {    // 若是文件
            Serial.print(" FILE: ");
            Serial.print(file.name());
            Serial.print(" SIZE: ");
            Serial.println(file.size());
        }
        // 遍历下一个文件
        file = root.openNextFile();
    }
}

// 创建目录
void createDir(fs::FS &fs, const char * path){
    Serial.printf("[Creating Dir]: %s\n", path);
    if (fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

// 移除目录
void removeDir(fs::FS &fs, const char * path){
    Serial.printf("[Removing Dir]: %s\n", path);
    if (fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

// 读文件
void readFile(fs::FS &fs, const char * path){
    Serial.printf("[Reading file]: %s\n", path);
     
    File file = fs.open(path);
    if (!file){
        Serial.println("Failed to open file for reading");
        return;
    }
     
    Serial.print("Read from file: ");
    while(file.available()){    // 遍历行读取
        Serial.write(file.read());
    }
    file.close();
}

// 创建写文件
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("[Writing file]: %s\n", path);
     
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if (file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

// 追加写文件
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("[Appending to file]: %s\n", path);
     
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if (file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

// 更名文件
void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("[Renaming file]: %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}


/*********************
 * Func:   判断是否存在文件 isExistFile
 * Author: xy
 * Date:   2023.3.26
 *********************/ 
bool FSIO_SD_IsExistFile(fs::FS &fs, const char * path) {
    Serial.printf("[Is Exist file]: %s\n", path);
    if (fs.exists(path)){   
        Serial.println("File exist");
		return true;
    } else {    // 文件不存在
        Serial.println("File not exist");
		return false;
    }
}


// 删除文件
void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("[Deleting file]: %s\n", path);
    if (fs.remove(path)){   
        Serial.println("File deleted");
    } else {    // 文件不存在
        Serial.println("Delete failed");
    }
}

// 测试文件IO
void testFileIO(fs::FS &fs, const char * path){
    Serial.printf("[Testing file IO]: %s\n", path);
    // 读文件
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;

    // 测试读文件消耗的时间
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if (toRead > 512){
                toRead = 512;
            }
            // 每次至多读取512字节数据
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }

    // 测试写文件消耗的时间
    file = fs.open(path, FILE_WRITE);
    if (!file){
        Serial.println("Failed to open file for writing");
        return;
    }
     
    size_t i;
    start = millis();
    for (i=0; i < 2048; i++){
        // 每次写入512字节数据
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}


