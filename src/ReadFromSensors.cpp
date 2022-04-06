#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 BMP;

bool bmpinit = false;

//-------------------------------------------------------Miscellaneous Functions--------------------------------------------------------//

// Converts float variables to char arrays.
void floatToString(float var, int dec_digits, char str[]) {
    int var_int = (int)var;
    int var_float = (int)((abs(var) - abs(var_int)) * pow(10, dec_digits));
    snprintf(str, 10, "%d.%d", var_int, var_float);
}

//-------------------------------------------------------Initialization Functions-------------------------------------------------------//

// Initializes BMP280
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