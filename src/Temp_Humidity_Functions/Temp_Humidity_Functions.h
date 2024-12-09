#ifndef _TEMP_HUM_FUN_
#define _TEMP_HUM_FUN_

#include <SHT4x.h>

bool initTempHumSensor();

void getTempHum(float &temp_C, float &hum_rH);


#endif