#ifndef _MEM_FUN_
#define _MEM_FUN_

#include <Arduino.h>
#include "hardware_connections.h"
#include "customDataTypes.h"
#include "FS.h"
#include <SD.h>
#include "SPI.h"

#define FILE_ACCEL_DATA "/acc_log.csv"
#define FILE_ENVIR_DATA "/env_log.csv"

bool initSDCard();

void writeTempData(tempHumInfo thi);

void writeAccData(AccInfo ai);

#endif