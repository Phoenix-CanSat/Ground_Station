#include <Arduino.h>

#include "Output.h"

// Prints the given text to the Serial with "INFO" identifier.
void Say(const char text[]) {
    Serial.print("INFO,");
    Serial.println(text);
    Serial.flush();
}