#ifndef _FS_IO_H_
#define _FS_IO_H_

#include "FS.h"
#include "SD.h"
#include "fs_io.h"

// File Created by xy
// 2023.2.12

// 列出目录
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

// 创建目录
void createDir(fs::FS &fs, const char * path);

// 移除目录
void removeDir(fs::FS &fs, const char * path);

// 读文件
void readFile(fs::FS &fs, const char * path);

// 创建写文件
void writeFile(fs::FS &fs, const char * path, const char * message);

// 追加写文件
void appendFile(fs::FS &fs, const char * path, const char * message);

// 更名文件
void renameFile(fs::FS &fs, const char * path1, const char * path2);

// 删除文件
void deleteFile(fs::FS &fs, const char * path);

// 测试文件IO
void testFileIO(fs::FS &fs, const char * path);

// 判断文件
bool FSIO_SD_IsExistFile(fs::FS &fs, const char * path);

#endif /* _FS_IO_H_ */

