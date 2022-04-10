#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "DataToSD.h"

#define SD_CS 10

bool sd_init = false;

uint32_t lastSaveTime = 0;

// Initializes SD card.
bool SDInit() {
    
    // If failed, send appropriate message.
    if (!SD.begin(SD_CS)) {
        return false;
    }

    // Removes previously created files if they exist (only "data_all.csv" and "data_gs.csv").
    if (SD.exists("data_all.csv")) {
        SD.remove("data_all.csv");
    }
    if (SD.exists("data_gs.csv")) {
        SD.remove("data_gs.csv");
    }

    // Initialization successful.
    sd_init = true;

    // Data file headers.
    SDWrite("PHX,Counter,Time,Temperature,Pressure,Latitude,Longitude,Altitude,Humidity,RSSI,GroundTemperature,GroundPressure", "data_all.csv");
    SDWrite("Time,GroundTemperature,GroundPressure", "data_gs.csv");

    return sd_init;
}

// Store text to given file.
bool SDWrite(const char text[], const char filename[]) {

    if (sd_init) {
        // Open file with given file name.
        File file = SD.open(filename, FILE_WRITE);

        // Store text in the file and close the file.
        if (file) {
            file.println(text);
            file.close();
            return true;
        }
    }
    return false;
}