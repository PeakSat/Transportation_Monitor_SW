#include "Accelerometer_Functions.h"

ADXL345 adxl = ADXL345();

bool initAccelerometer(){
    adxl.powerOn();
    adxl.setRangeSetting(4);            // Give the range settings
                                        // Accepted values are 2g, 4g, 8g or 16g
                                        // Higher Values = Wider Measurement Range
                                        // Lower Values = Greater Sensitivity

    // adxl.setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
    // adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment
    // adxl.setImportantInterruptMapping(0, 0, 1, 0, 0);
    // adxl.FreeFallINT(1);

    return true;
}

// Results in mg
void readAccValues(int &x, int &y, int &z){ 
    adxl.readAccel(&x, &y, &z);
}

void getGValues(double &x, double &y, double &z){
    double xyz[3];
    adxl.get_Gxyz(xyz);
    x = xyz[0];
    y = xyz[1];
    z = xyz[2];
}

void enterAccLowPower(){
    adxl.setLowPower(true);
}

void exitAccLowPower(){
    adxl.setLowPower(false);
}