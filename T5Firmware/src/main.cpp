#include <Arduino.h>
#include <SensorModule.h>
#include <Display.h>
#include <SensorSelection.h>
#include <MicroSDCardOperations.h>
#include <ArduinoJson.h>
#include <EventDrivenButtonPress.h>
/*Libraries included via project 'lib' folder:
* GxEPD
* esp32-micro-sdcard
*/

//Sleep variables
#define uS_TO_S_FACTOR 1000000 // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 5        // Time ESP32 will go to sleep (in seconds)

//Global JSON document which stores the configuration info as stored on the MicroSD card.
DynamicJsonDocument configDoc(256);

void setup() 
{
  //Instance variables of custom classes which provide methods required to be called from main.cpp.
  SensorModule sensorModule;
  SensorSelection sensorSelection;
  MicroSDCardOperations microSDCardOperations;
  EventDrivenButtonPress eventDrivenButtonPress;
  WiFiConnection wiFiConnection;
  Display display;

  Serial.begin(115200);
  delay(500);
  eventDrivenButtonPress.initialise();
  delay(500);

  //displays home page showing Dandelion logo & wifi connection status.
  display.setupDisplay();

  //read in config data from MicroSD card
  configDoc = microSDCardOperations.getConfigData();

  //connect to wifi
  wiFiConnection.connectToWiFi();

  sensorSelection.setAndLevelSelection();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void loop() 
{}

