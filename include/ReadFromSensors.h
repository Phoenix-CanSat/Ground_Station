#ifndef READFROMSENSORS_FUNCTIONS_H
#define READFROMSENSORS_FUNCTIONS_H

#include <Arduino.h>

//-------------------------------------------------------Miscellaneous Functions--------------------------------------------------------//

/// Converts float variables to char arrays.
void floatToString(float var, int dec_digits, char str[]);

//-------------------------------------------------------Initialization Functions-------------------------------------------------------//

/// Initializes respective sensor.
/// @return true if initialization is successful.
/// @return false if initialization is unsuccessful.
bool BMPInit();

//-----------------------------------------------------Read From Sensors Functions------------------------------------------------------//

/// Reads required value from respective sensor.
/// @return value in float.
float GetGroundTemperature();           // Ground Temperature in Celsius (°C).
float GetGroundPressure();              // Ground Pressure in HectoPascal/Millibar (hPa/mbar).

#endif