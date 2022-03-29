#include <Arduino.h>

#include "Initialization.h"
#include "Time.h"
#include "DataToSD.h"
#include "RF.h"
#include "ReadFromSensors.h"

/* uint32_t packetCounter;
uint32_t trasnmitionTime;
float temperature;
float pressure;
float latitude;
float longitude;
float altitude;
float humidity;

void Parse() {
  if (Serial.available()) {
    packetCounter = Serial.parseInt();
    trasnmitionTime = Serial.parseInt();
    temperature = Serial.parseFloat();
    pressure = Serial.parseFloat();
    latitude = Serial.parseFloat();
    longitude = Serial.parseFloat();
    altitude = Serial.parseFloat();
    humidity = Serial.parseFloat();
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
  char datags[225];

  // Waits untill data is received
  while (!RFReceiveData(data) && Time()-time<=StandByTime);
  if (Time()-time<=StandByTime) {
    snprintf(data, 225, "%s,%s,%s", data, GTempStr, GPresStr);
    SDWrite(data, "dataall");
    Serial.println(data);
    Serial.flush();
    consequtivePacketsLost = 0;
  } else {
    consequtivePacketsLost += 1;
    if (consequtivePacketsLost >= 2 && StandByTime < MAXSTANDBYTIME) {
      StandByTime += 50;
    }
  }

  snprintf(datags, 225, "%lu,%s,%s", time, GTempStr, GPresStr);
  SDWrite(datags, "datags");

  // Parse();

  // TODO: Add SD support.

  yield();
}