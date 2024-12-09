#include "Temp_Humidity_Functions.h"

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

bool initTempHumSensor(){
    if(!sht4.begin()){
        return false;
    }
    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    sht4.setHeater(SHT4X_NO_HEATER);
    return true;
}

void getTempHum(float &temp_C, float &hum_rH){
    sensors_event_t humidity, temp;
    sht4.getEvent(&humidity, &temp);
    temp_C = temp.temperature;
    hum_rH = humidity.relative_humidity;
}