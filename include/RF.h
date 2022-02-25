#ifndef RF_FUNCTIONS_H
#define RF_FUNCTIONS_H

#include <Arduino.h>

/// Initializes RFM9X.
/// Sets frequency.
/// @return true if initialization is successful and frequency was set.
/// @return false if initialization is unsuccessful or frequency could not be set.
bool RFInit();

/// Attempts to receive packet from CanSat.
void RFReceiveData();

#endif