#ifndef _HARDWARE_CONNECTIONS_H_
#define _HARDWARE_CONNECTIONS_H_

// I2C BUS
// ADXL345BCCZ      0x53 (Accelerometer)
// SEN-18364        Not Connected
// SHT41            0x38 (Temp & Humidity sensor)

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

// SPI
// SD card connector

#define SD_CS_PIN       5       
#define SD_CD_PIN       37      // Card detect pin
#define SPI_MOSI_PIN    13
#define SPI_MISO_PIN    19
#define SPI_CLK_PIN     14

// LEDs

#define LED_GREEN_PIN   25
#define LED_BLUE_PIN    26

// Vibration Sensor

#define VIBE_SENSOR_PIN 36

#endif