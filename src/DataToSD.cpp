#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "DataToSD.h"

#define SD_CS 10

bool sd_init = false;

// Initializes SD card.
bool SDInit() {
    
    // If failed, send appropriate message.
    if (!SD.begin(SD_CS)) {
        return false;
    }

    // Removes previously created files if they exist (only "DATA" and "LOGGER").
    if (SD.exists("dataall")) {
        SD.remove("dataall");
    }
    if (SD.exists("datags")) {
        SD.remove("datags");
    }

    // Initialization successful.
    sd_init = true;

    // Data file header.
    SDWrite("Time,Temperature,Pressure,Latitude,Longitude,Altitude,Humidity,GroundTemperature,GroundPressure", "dataall");
    SDWrite("GroundTemperature,GroundPressure", "datags");

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