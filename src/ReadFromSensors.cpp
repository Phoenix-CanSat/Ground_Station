#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 BMP;

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
        return (float)NAN;
    } else {
        return BMP.readTemperature();
    }
}

// Ground Pressure in HectoPascal/Millibar (hPa/mbar).
float GetGroundPressure() {
    // No value if BMP280 isn't initialized.
    if (!bmpinit) {
        return (float)NAN;
    } else {
        return BMP.readPressure() / 100.0F;
    }
}