//#pragma once  
#ifndef __BH1750_H
#define __BH1750_H

#include <Arduino.h>

#define bh1750TimeInterval 1000 //检测一次的时间间隔,1秒
#define BH1750_OK   0
#define BH1750_ERR   -1

void BH1750_Init(void);
int BH1750_Read(int address);
void BH1750_ShowData(void);
int BH1750_GetData(void);

#endif