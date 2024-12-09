#ifndef _CUSTOM_DT_
#define _CUSTOM_DT_

#include <Arduino.h>

typedef struct{  
  unsigned long timestamp;

  int rawAccX;
  int rawAccY;
  int rawAccZ;

  double GX;
  double GY;
  double GZ;

}AccInfo;

typedef struct{  
  unsigned long timestamp; 
  
  float temp_C;
  float hum_rH;

}tempHumInfo;

#endif