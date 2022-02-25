#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "RF.h"

#define RFM_CS 53
#define RFM_RST 2
#define RFM_INT 3

RH_RF95 rf(RFM_CS, RFM_INT);
bool rfInit_ = false;

// Initializes RFM9X.
bool RFInit() {

    // Resets RFM.
    pinMode(RFM_RST, OUTPUT);
    digitalWrite(RFM_RST, LOW);
    delay(100);
    digitalWrite(RFM_RST, HIGH);
    delay(100);

    // If failed, send appropriate message.
    if (!rf.init()) {
        Serial.println("Could not initialize the RF.");
    }

    // Sets RFM frequency to 433.2
    else if (!rf.setFrequency(433.2)) {
        Serial.println("Could not set the RF frequency to 433.2 Hz.");
    }
    
    else {
        //Initialization successful.
        rfInit_ = true;
    }

    return rfInit_;
}

void RFReceiveData() {
    
    if (!rfInit_) {
        Serial.println("RF is not initialized.");
        while (1);
    }

    uint8_t packet[225];
    uint8_t len = sizeof(packet);

    if (rf.recv(packet, &len)){
        Serial.println((char*)packet);
    }
}