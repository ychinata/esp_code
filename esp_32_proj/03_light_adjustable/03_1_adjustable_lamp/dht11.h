//#pragma once  
#ifndef __DTH11_H
#define __DTH11_H

#include <Arduino.h>

void DHT11_Init();
void DHT11_Getdata(float* humidity, float* temp);
void DHT11_Showdata();

#endif