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

#define MAXSTANDBYTIME 500
#define MINSTANDBYTIME 250

uint32_t StandByTime = MINSTANDBYTIME;
uint8_t consequtivePacketsLost = 0;

void floatToString(float var, int dec_digits, char str[]) {
  int var_int = (int)var;
  int var_float = (int)((abs(var) - abs(var_int)) * pow(10, dec_digits));
  snprintf(str, 10, "%d.%d", var_int, var_float);
}

void setup() {
  while (!Serial);
  // Initializes Serial and Ground Station.
  Serial.begin(9600);
  InitializeGroundStation();
  CalculateInitTime();
}

void loop() {

  // Time data was read.
  uint32_t time = Time();

  // Stores GS sensor values to appropriate variables.
  float groundtemperature = GetGroundTemperature();
  float groundpressure = GetGroundPressure();

  // Converts values to strings.
  char GTempStr[10];
  char GPresStr[10];
  floatToString(groundtemperature, 2, GTempStr);
  floatToString(groundpressure, 2, GPresStr);

  char data[225];

  // Waits untill data is received
  while (!RFReceiveData(data) && Time()-time<=StandByTime);
  if (Time()-time<=StandByTime) {
    snprintf(data, 225, "%s,%s,%s", data, GTempStr, GPresStr);
    //Parse();
    consequtivePacketsLost = 0;
  } else {
    snprintf(data, 225, "%lu,%s,%s", time, GTempStr, GPresStr);
    consequtivePacketsLost += 1;
    if (consequtivePacketsLost >= 2 && StandByTime <= MAXSTANDBYTIME) {
      StandByTime += 50;
    }
  }
  Serial.println(data);
  Serial.flush();

  yield();
} 