#include <Arduino.h>

#include "Initialization.h"
#include "Timer.h"
#include "DataToSD.h"
#include "RF.h"
#include "ReadFromSensors.h"

//------------------------------------------------------------Initialization------------------------------------------------------------//

void setup() {

  // Initializes Serial and Ground Station.
  while (!Serial);
  Serial.begin(9600);

  // Initializes Systems and Sensors.
  InitializeGroundStation();

  // Calculates initialization time.
  CalculateInitTime();
}

void loop() {

//--------------------------------------------------------Get Data From Sensors---------------------------------------------------------//

  // Time data is read.
  uint32_t time = Time();

  // Stores GS sensor values to appropriate variables.
  float groundtemperature = GetGroundTemperature();
  float groundpressure = GetGroundPressure();

  // Converts values to strings.
  char GTempStr[10];
  char GPresStr[10];
  floatToString(groundtemperature, 2, GTempStr);
  floatToString(groundpressure, 2, GPresStr);

  char data[200];
  char datags[100];

//-------------------------------------------------Store All Data and Print to Serial---------------------------------------------------//

  // If data received from Bob:
  if (RFReceiveData(data)) {

    // Merges with Ground Station data.
    snprintf(data, 225, "%s,%s,%s", data, GTempStr, GPresStr);
    
    // Saves data to "data_all.csv" file.
    SDWrite(data, "data_all.csv");

    // Print data to Serial.
    Serial.println(data);
    Serial.flush();
  }

//---------------------------------------------------Store Ground Station Data to SD----------------------------------------------------//

  // Stores Ground Station data separately in "data_gs.csv".
  snprintf(datags, 225, "%lu,%s,%s", time, GTempStr, GPresStr);
  //SDWrite(datags, "data_gs.csv");

  yield();
}