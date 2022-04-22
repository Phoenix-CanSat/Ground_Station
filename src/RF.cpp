#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>

#include "RF.h"
#include "Output.h"

#define FAKEDATA true

int8_t fakeData = 0;

#define RFM_CS 53
#define RFM_RST 2
#define RFM_INT 3

RH_RF95 rf(RFM_CS, RFM_INT);
bool rf_init = false;

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
        return rf_init;
    }

    // Sets RFM frequency to 433.2
    else if (!rf.setFrequency(433.2)) {
        Say("RF freq not set.");
    }
    
    else {
        // Sets the transmitter power output level.
        rf.setTxPower(23, false);

        //Initialization successful.
        rf_init = true;
    }

    return rf_init;
}

// Checks if data from Bob is received.
bool RFReceiveData(char data[]) {
    
    if (FAKEDATA) {
        if (fakeData == 5) {
            snprintf(data, 225, "PHX,1,1000,22.53,1014.48,3808.5532,2400.8757,-0.19,35.07,30.00,-56");
            return true;
        } else {
            fakeData += 1;
            return false;
        }
    }

    if (rf_init) {

        uint8_t packet[225];
        uint8_t len = sizeof(packet);

        // Attempts to receive packet.
        if (rf.recv(packet, &len)) {
            packet[len] = '\0';

            // Checks for packet identifier in the packet received.
            if (packet[0] == 'P' && packet[1] == 'H' && packet[2] == 'X') {

                // Stores the packet and its RSSI to the data string.
                snprintf(data, 225, "%s,%d", (char*)packet, rf.lastRssi());
                return true;
            }
        }
    }

    return false;
}