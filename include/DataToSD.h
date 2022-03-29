#ifndef DATATOSD_FUNCTIONS_H
#define DATATOSD_FUNCTIONS_H

#include <Arduino.h>

/// Initializes SD card.
/// Removes previously created files with names "DATA_ALL" and "DATA_GS" if they exist.
/// @return true if initialization is successful.
/// @return false if initialization fails or an SD card is not connected.
bool SDInit();

/// Store text to given file.
/// @return true if text is stored.
/// @return false if file could not be opened or SD wasn't initialized.
bool SDWrite(const char text[], const char filename[]);

#endif