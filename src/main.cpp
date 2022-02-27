#include <Arduino.h>

#include "Initialization.h"
#include "RF.h"
#include "ReadFromSensors.h"

#define INITTIME 5000

/* #define X 0
#define Y 1
#define Z 2

uint32_t time = 0;
float temperature = 0;
float pressure = 0;
float latitude = 0;
float longitude = 0;
float altitude = 0;
float humidity = 0;
float magnetic[3] = {0, 0, 0};
float gravity[3] = {0, 0, 0};

void Parse() {
  if (Serial.available()) {
    time = Serial.parseInt();
    temperature = Serial.parseFloat();
    pressure = Serial.parseFloat();
    latitude = Serial.parseFloat();
    longitude = Serial.parseFloat();
    altitude = Serial.parseFloat();
    humidity = Serial.parseFloat();
    magnetic[X] = Serial.parseFloat();
    magnetic[Y] = Serial.parseFloat();
    magnetic[Z] = Serial.parseFloat();
    gravity[X] = Serial.parseFloat();
    gravity[Y] = Serial.parseFloat();
    gravity[Z] = Serial.parseFloat();
  }
} */

// Returns the time in milliseconds (ms) since completion of initialization.
uint32_t Time() {
  return millis() - INITTIME;
}

void setup() {
  while (!Serial);
  // Initializes Serial and Ground Station.
  Serial.begin(115200);
  InitializeGroundStation();
  
  if (millis() <= INITTIME) {
    delay(INITTIME - millis());
  }
}

void loop() {

  float groundtemperature = GetGroundTemperature();
  float groundpressure = GetGroundPressure();
  char data[225];

  if (RFReceiveData(data)) {
    snprintf(data, 225, "%s,%.2f,%.2f", data, groundtemperature, groundpressure);
    //Parse();
    Serial.println(data);
    Serial.flush();
  } else {
    snprintf(data, 225, "%.2f,%.2f", groundtemperature, groundpressure);
  }
  
  yield();
}