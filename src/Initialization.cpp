#include <Arduino.h>

#include "Initialization.h"
#include "Output.h"
#include "DataToSD.h"
#include "RF.h"
#include "ReadFromSensors.h"

void InitializeGroundStation() {
    
    Say("Initializing Ground Station...");

//--------------------------------------------------------------------------------------------------------------------------------------//

    // Initializes micro SD card.
    if (SDInit()) {
        Say("SD init.");
    } else {
        Say("SD not init.");
    }

    // Initializes RFM9X.
    if (RFInit()) {
        Say("RF init.");
    } else {
        Say("RF not init.");
    }

    // Initializes BMP280.
    if (BMPInit()) {
        Say("BMP init.");
    } else {
        Say("BMP not init.");
    }

//--------------------------------------------------------------------------------------------------------------------------------------//

    Say("Ground Station Initialized.");
    
}