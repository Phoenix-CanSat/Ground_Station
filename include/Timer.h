#ifndef TIMER_FUNCTIONS_H
#define TIMER_FUNCTIONS_H

#include <Arduino.h>

/// Sets the time in milliseconds (ms) after boot as the time since completion of initialization.
void CalculateInitTime();

/// @return the time in milliseconds (ms) since completion of initialization.
uint32_t Time();

#endif