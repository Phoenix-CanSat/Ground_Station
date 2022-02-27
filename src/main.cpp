#include <Arduino.h>

#include "Initialization.h"
#include "Time.h"
#include "RF.h"
#include "ReadFromSensors.h"

/* #define X 0
#define Y 1
#define Z 2

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

void setup() {
  while (!Serial);
  // Initializes Serial and Ground Station.
  Serial.begin(115200);
  InitializeGroundStation();
  CalculateInitTime();
}

void loop() {

  // Time data was read.
  int time = Time();

  // Stores GS sensor values to appropriate variables.
  double groundtemperature = GetGroundTemperature();
  double groundpressure = GetGroundPressure();
  
  char data[225];
  if (RFReceiveData(data)) {
    snprintf(data, 225, "%s,%.2f,%.2f", data, groundtemperature, groundpressure);
    //Parse();
    Serial.println(data);
    Serial.flush();
  } else {
    snprintf(data, 225, "%d,%.2f,%.2f", time, groundtemperature, groundpressure);
  }
  
  yield();
}