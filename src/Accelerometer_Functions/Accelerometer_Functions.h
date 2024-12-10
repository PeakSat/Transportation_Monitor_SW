#ifndef _ACC_FUN_
#define _ACC_FUN_

#include <Arduino.h>
#include <Wire.h>
#include <ADXL345.h>

bool initAccelerometer();

void readAccValues(int &x, int &y, int &z);

void getGValues(double &x, double &y, double &z);

void enterAccLowPower();

void exitAccLowPower();

#endif