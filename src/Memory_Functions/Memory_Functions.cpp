#include "Memory_Functions.h"

void readFile(fs::FS &fs, const char *path) {
    //Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        //Serial.println("Failed to open file for reading");
        return;
    }

    while (file.available()) {
        //Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
    File file;
    if(!fs.exists(path)){
        file = fs.open(path, FILE_WRITE);
    }else{
        file = fs.open(path, FILE_APPEND);
    }
    if (!file) {
        return;
    }
    if(file.print(message)){
        //Serial.println("File Written");
    }else{
        //Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        return;
    }
    file.print(message);
    file.close();
}


bool initSDCard(){
    SPI.begin(SPI_CLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SD_CS_PIN);
    if(!SD.begin(SD_CS_PIN)){
        return false;
    }
    uint8_t card_type = SD.cardType();
    if(card_type == CARD_NONE){
        //Serial.println("No SD card attached?");
        return false;
    }
    return true;

}

void writeTempData(tempHumInfo thi){
    String dataToWrite;
    dataToWrite+=(String(thi.timestamp)+",");
    dataToWrite+=(String(thi.temp_C)+",");
    dataToWrite+=(String(thi.hum_rH)+"\n");

    writeFile(SD, FILE_ENVIR_DATA, dataToWrite.c_str());
}

void writeAccData(AccInfo ai){
    String dataToWrite;
    dataToWrite+=(String(ai.timestamp)+",");
    dataToWrite+=(String(ai.rawAccX)+",");
    dataToWrite+=(String(ai.rawAccY)+",");
    dataToWrite+=(String(ai.rawAccZ)+",");
    dataToWrite+=(String(ai.GX)+",");
    dataToWrite+=(String(ai.GY)+",");
    dataToWrite+=(String(ai.GZ)+"\n");

    writeFile(SD, FILE_ACCEL_DATA, dataToWrite.c_str()); 
}