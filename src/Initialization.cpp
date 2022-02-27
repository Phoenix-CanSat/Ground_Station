#include <Arduino.h>

#include "Initialization.h"
#include "RF.h"
#include "ReadFromSensors.h"

void InitializeGroundStation() {
    
    Serial.println("\nInitializing Ground Station...\n");

//--------------------------------------------------------------------------------------------------------------------------------------//

    // Initializes RFM9X.
    if (RFInit()) {
        Serial.println("RF initialized.");
    } else {
        Serial.println("RF not initialized.");
    }

    // Initializes BMP280.
    if (BMPInit()) {
        Serial.println("BMP280 initialized.");
    } else {
        Serial.println("BMP280 not initialized.");
    }

//--------------------------------------------------------------------------------------------------------------------------------------//

    Serial.println("\nInitialization Completed.\n");
}