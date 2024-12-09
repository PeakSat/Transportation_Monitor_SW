#include <Arduino.h>
#include "hardware_connections.h"
#include "defaultDefinitions.h"
#include "customDataTypes.h"
#include "Accelerometer_Functions/Accelerometer_Functions.h"
#include "Temp_Humidity_Functions/Temp_Humidity_Functions.h"
#include "Memory_Functions/Memory_Functions.h"

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR unsigned long timekeeper = 0;

bool sampleTemp = false;
bool sampleAcc  = false;

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); sampleAcc  = true; break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); sampleTemp = true; break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

void goToSleep(){
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, LOW);
  esp_deep_sleep_start();
}

void handleAccData(){
  AccInfo info_arr[ACC_SAMPLES];
  for(uint8_t i=0;i<ACC_SAMPLES;i++){
    info_arr[i].timestamp = millis()+timekeeper;
    readAccValues(info_arr[i].rawAccX, info_arr[i].rawAccY, info_arr[i].rawAccZ);
    getGValues(info_arr[i].GX, info_arr[i].GY, info_arr[i].GZ);
    delay((1000/SAMPLE_RATE_HZ));
  }

  for(uint8_t i=0;i<ACC_SAMPLES;i++){
    writeAccData(info_arr[i]);
  }

}

void handleTempData(){
  tempHumInfo ti_info;
  ti_info.timestamp = millis()+timekeeper;
  getTempHum(ti_info.temp_C, ti_info.hum_rH);
  writeTempData(ti_info);
}

unsigned long debounceTimer = 0;

void vibeISR(){
  if(millis()-debounceTimer<2000 ){
    return;
  }
  sampleAcc = true;
  
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  print_wakeup_reason();

  ++bootCount;
  Serial.println("Boot Count: " + String(bootCount));

  pinMode(VIBE_SENSOR_PIN, INPUT);

  if(!initAccelerometer()){
    Serial.println("Error initialising accelerometer");
    delay(3000);
    esp_restart();
  }
  Serial.println("Accelerometer initialised successfully");

  if(!initTempHumSensor()){
    Serial.println("Error initialising Temp&Hum Sensor");
    delay(3000);
    esp_restart();
  }
  Serial.println("Temp&Hum Sensor initialised successfully");

  if(!initSDCard()){
    Serial.println("Error initialising SD Card");
    delay(3000);
    esp_restart();
  }
  Serial.println("SD Card initialised successfully");

}

void loop() {

  if(sampleTemp){
    handleTempData();
  }else if(sampleAcc){
    debounceTimer = millis();
    attachInterrupt(VIBE_SENSOR_PIN, vibeISR, FALLING);
    while(sampleAcc){
      sampleAcc = false;
      handleAccData();
    }
  }else{
    Serial.println("Error Wake up?");
  }
  timekeeper += millis();
  goToSleep();
}
