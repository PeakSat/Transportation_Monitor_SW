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

void lightGreenLed(){
  digitalWrite(LED_GREEN_PIN, HIGH);
  delay(100);
  digitalWrite(LED_GREEN_PIN, LOW);  
}

void lightBlueLed(){
  pinMode(LED_BLUE_PIN, OUTPUT);
  digitalWrite(LED_BLUE_PIN, HIGH);
  delay(200);
  digitalWrite(LED_BLUE_PIN, LOW);
}


void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : sampleAcc  = true; timekeeper+=10000; break;
    case ESP_SLEEP_WAKEUP_EXT1 : break;
    case ESP_SLEEP_WAKEUP_TIMER :sampleTemp = true; timekeeper+=10000; break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : break;
    case ESP_SLEEP_WAKEUP_ULP : break;
    default : break;
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
  debounceTimer = millis();
  
}

void setup() {
  // Initialize serial communication
  setCpuFrequencyMhz(10);
  //Serial.begin(115200);
  print_wakeup_reason();

  ++bootCount;
  // Serial.println("Boot Count: " + String(bootCount));

  pinMode(VIBE_SENSOR_PIN, INPUT);
  if(!initAccelerometer()){
    //Serial.println("Error initialising accelerometer");
    delay(1000);
    esp_restart();
  }
  // Serial.println("Accelerometer initialised successfully");

  if(!initTempHumSensor()){
    //Serial.println("Error initialising Temp&Hum Sensor");
    delay(1000);
    esp_restart();
  }
  // Serial.println("Temp&Hum Sensor initialised successfully");

  if(!initSDCard()){
    //Serial.println("Error initialising SD Card");
    delay(1000);
    esp_restart();
  }
  // Serial.println("SD Card initialised successfully"); 

  if(bootCount<2){
    pinMode(LED_GREEN_PIN, OUTPUT); 
    lightGreenLed();
  }

}

void loop() {

  if(sampleTemp){
    handleTempData();
    lightBlueLed();
  }else if(sampleAcc){
    exitAccLowPower();
    debounceTimer = millis();
    attachInterrupt(VIBE_SENSOR_PIN, vibeISR, FALLING);
    while(sampleAcc){
      sampleAcc = false;
      handleAccData();
    }
    enterAccLowPower();
    handleTempData();
    lightBlueLed();
  }else{
    //Serial.println("Error Wake up?");
  }
  timekeeper += millis();
  goToSleep();
}
