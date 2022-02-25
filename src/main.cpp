#include <Arduino.h>

#include "Initialization.h"
#include "RF.h"

void setup() {

  // Initializes Serial and Ground Station.
  while(!Serial);
  Serial.begin(115200);
  InitializeGroundStation();

}

void loop() {
  RFReceiveData();
}