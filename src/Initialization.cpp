#include "Initialization.h"
#include "RF.h"

void InitializeGroundStation() {
    
    Serial.println("\nInitializing Ground Station...\n");

//--------------------------------------------------------------------------------------------------------------------------------------//

    // Initializes RFM9X.
    if (RFInit()) {
        Serial.println("RF initialized.");
    } else {
        Serial.println("RF not initialized.");
    }

    //--------------------------------------------------------------------------------------------------------------------------------------//

    Serial.println("\nInitialization Completed.\n");
}