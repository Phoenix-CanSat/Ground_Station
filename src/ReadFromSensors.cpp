#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11
#define BMP_CS 10

Adafruit_BMP280 BMP;  // I2C
// Adafruit_BMP280 BMP(BMP_CS); // hardware SPI
// Adafruit_BMP280 BMP(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

bool bmpinit = false;

//-------------------------------------------------------Initialization Functions-------------------------------------------------------//

//  Initializes BMP280
bool BMPInit() {
    if (BMP.begin()) {
        bmpinit = true;
    }
    return bmpinit;
}

//-----------------------------------------------------Read From Sensors Functions------------------------------------------------------//

// Ground Temperature in Celsius (°C).
float GetGroundTemperature() {
    // No value if BMP280 isn't initialized.
    if (!bmpinit) {
        return 0;
    } else {
        return BMP.readTemperature();
    }
}

// Ground Pressure in HectoPascal/Millibar (hPa/mbar).
float GetGroundPressure() {
    // No value if BMP280 isn't initialized.
    if (!bmpinit) {
        return 0;
    } else {
        return BMP.readPressure() / 100.0F;
    }
}