#include <Arduino.h>

#include "Initialization.h"
#include "DataToSD.h"
#include "RF.h"
#include "ReadFromSensors.h"

void InitializeGroundStation() {
    
    Serial.println("\nInitializing Ground Station...\n");

//--------------------------------------------------------------------------------------------------------------------------------------//

    // Initializes micro SD card.
    if (SDInit()) {
        Serial.println("SD init.");
    } else {
        Serial.println("SD not init.");
    }

    // Initializes RFM9X.
    if (RFInit()) {
        Serial.println("RF init.");
    } else {
        Serial.println("RF not init.");
    }

    // Initializes BMP280.
    if (BMPInit()) {
        Serial.println("BMP init.");
    } else {
        Serial.println("BMP not init.");
    }

//--------------------------------------------------------------------------------------------------------------------------------------//

    Serial.println("\nGround Station Initialized.\n");
    
}